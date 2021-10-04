#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <thread>
//torch
#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>
//grpc
#include <grpcpp/grpcpp.h>
//#include <sendReceiveWeights.proto/grpcpp.h>
#include "proto/sendReceiveWeights.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using params::Parameters;
using params::WeightsPasser;
//using params::WeightsToClient;
//using params::WeightsToServer;

//----------------------------------------------------------------------------
//simple network
struct Network : torch::nn::Module {
Network() {
        layer1 = register_module("layer1", torch::nn::Linear(784, 64));
        layer2 = register_module("layer2", torch::nn::Linear(64, 32));
        output = register_module("output", torch::nn::Linear(32, 10));
    }
    
    //network algorithm
    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(layer1->forward(x.reshape({x.size(0), 784})));
        x = torch::dropout(x, 0.5, is_training());
        
        x = torch::relu(layer2->forward(x));
        x = torch::log_softmax(output->forward(x), 1);
        return x;
    }
    
    torch::Tensor prediction;
    torch::Tensor loss;
    //defining the layers
    torch::nn::Linear layer1{nullptr}, layer2{nullptr}, output{nullptr};
};


//----------------------------------------------------------------------------
class Client {
public:
    Client(std::shared_ptr<Channel> channel)
        : stub_(WeightsPasser::NewStub(channel)),
          net(std::make_shared<Network>()) {}

    //--------------------------------------------------------------------------
    //actual method that sends the weights to the server
    /*std::string sendWeights(const std::string &weights, std::string tensorType) {
        //sending the weights to the server
        params::WeightsToServer clientWeights;
        clientWeights.set_parameters(std::string(weights.begin(), weights.end()));
        clientWeights.set_tensor_type(tensorType);

        //receiving the response from the server
        params::WeightsToClient serverWeights;

        ClientContext context;
        Status status = stub_->sendWeights(&context, clientWeights, &serverWeights);
        
        if (status.ok()) {
            return serverWeights.reply();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                       << std::endl;
            return "RPC failed\n";
        }
    }*/
    //--------------------------------------------------------------------------

    //method that threads use to pack up the parameters
    static void sendThread(
        std::shared_ptr<ClientReaderWriter<Parameters, Parameters>> stream,
        Parameters model,
        const std::string &weights, 
        std::string tensorType) {

        model.set_parameters(weights);
        model.set_tensor_type(tensorType);
        stream->Write(model);
        stream->WritesDone();
    }

    //bidirectional method
    std::string streamWeights(const std::string &weights, std::string tensorType) {
        ClientContext context;
        Parameters clientModel, serverModel;
        std::shared_ptr<ClientReaderWriter<Parameters, Parameters>> stream(
            stub_->streamWeights(&context)
        );

        //thread makes it more modular?
        std::thread writer(sendThread, stream, clientModel, weights, tensorType);

        //reading side of the read/write stream
        while (stream->Read(&serverModel)) {
            std::cout << "got it\n";
        }
        std::cout << "done reading\n";

        writer.join();
        Status status = stream->Finish();
        if (status.ok()) {
            return "ye\n";
        }
        else {
            return "no do\n";
        }
    }

    //server-side stream method
    std::string sendWeights(const std::string& weights, std::string tensorType) {
        ClientContext context;
        Parameters clientModel;

        //pack up the weights
        clientModel.set_parameters(weights);
        clientModel.set_tensor_type(tensorType);

        //call the stub
        std::unique_ptr<ClientReader<Parameters>> reader(
            stub_->sendWeights(&context, clientModel)
        );

        //make a clientReader
        while (reader->Read(&clientModel)) {
            std::cout << "Read Params\n";
        }

        //load the features back in

        return "temp return\n";
    }

    /*-------remove later-------*/
    void writeToFile(std::string fileName) {
        std::fstream writeTo;

        writeTo.open(fileName, std::ios::out);
        writeTo << net->parameters();
        writeTo.close();
    }

    void runModel() {
        //torch locals
        int kNoiseSize = 1;
        int kBatchSize = 64;
        int batches_per_epoch = 938;
        int kNumberOfEpochs = 10;

        //create the data loader
        auto data_loader = torch::data::make_data_loader(
            torch::data::datasets::MNIST("../mnist").map(torch::data::transforms::Stack<>()), /*batch size*/ 64);

        //make the optimizer
        torch::optim::SGD optimizer(net->parameters(), 0.01);

        //loop for actually running the network
            //comments for me to have a better idea on how the model works
        for (size_t epoch = 1; epoch <= 2; ++epoch) {
            size_t batch_index = 0;
            
            //iterate the data loader to get the data
            for (auto& batch : *data_loader) {
                //reset the gradients
                optimizer.zero_grad();
                //execute the model on the input data
                //torch::Tensor prediction = net->forward(batch.data);
                net->prediction = net->forward(batch.data);
                //compute a loss bvalue to judge the prediction of the model
                //torch::Tensor loss = torch::nll_loss(prediction, batch.target);
                net->loss = torch::nll_loss(net->prediction, batch.target);
                //compute grandients of the loss with respect to the parameters of the model
                //loss.backward(); //back propogation
                net->loss.backward(); //back propogation
                //update the parameters based on the calculated gradients
                optimizer.step();
                //output the loss and checkpoint of every hundred batches
                if (++batch_index % 100 == 0) {
                    std::cout << "Epochs: " << epoch << " | Batch: " 
                        << batch_index << " | Loss: " << net->loss.item<float>() << std::endl;
                }
            }
        }

        writeToFile("weights.txt");

        //send the weights to the server
        std::stringstream weights;
        torch::save(net, weights);
        std::string layer("Layer2");
        //std::string reply = sendWeights(weights.str(), layer);
        std::string reply = streamWeights(weights.str(), layer);
        std::cout << "Server received tensor: " << reply << std::endl;
    }

private:
    std::shared_ptr<Network> net;
    std::unique_ptr<WeightsPasser::Stub> stub_;
};


//----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    std::string targetString = "localhost:50051";

    //make the service
    Client client(
        grpc::CreateChannel(targetString, grpc::InsecureChannelCredentials()));

    client.runModel();
    
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
