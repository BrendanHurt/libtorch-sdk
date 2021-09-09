#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
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
using params::weightsPasser;
using params::WeightsToClient;
using params::WeightsToServer;

class Client {
public:
    Client(std::shared_ptr<Channel> channel)
        : stub_(weightsPasser::NewStub(channel)) {}

    //actual method that sends the weights to the server
    std::string sendWeights(const std::string &weights, std::string tensorType) {
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
    }
private:
    std::unique_ptr<weightsPasser::Stub> stub_;
};

int main(int argc, char* argv[]) {
    //proto locals
    params::WeightsToServer clientSideWeights;
    params::WeightsToClient serverSideWeights;
    ClientContext context;
    Status status;
    std::string targetString = "localhost:50051";

    //torch locals
    int kNoiseSize = 1;
    int kBatchSize = 64;
    int batches_per_epoch = 938;
    int kNumberOfEpochs = 10;

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

    //create a new network
    auto net = std::make_shared<Network>();
    std::shared_ptr<Network> Net(new Network);

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
    


    //make the service
    Client client(
        grpc::CreateChannel(targetString, grpc::InsecureChannelCredentials()));

    //send the weights to the server
    std::stringstream weights;
    torch::save(net, weights);
    torch::load(Net, weights);
    std::string layer("Layer2");
    std::string reply = client.sendWeights(weights.str(), layer);
    std::cout << "Server received tensor: " << reply << std::endl;

    
    //write the weights out so they can be checked against the receiving weights
    std::fstream output;
    output.open("weights.txt", std::ios::out);
    output << net->parameters();
    output.close();

    //now the loaded model
    /*output.open("loadedWeights.txt", std::ios::out);
    output << Net->layer2->weight;
    output.close();*/
    
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
