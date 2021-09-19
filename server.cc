#include <iostream>
#include <memory>
#include <string>

//torch
#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>

//grpc & proto
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "proto/sendReceiveWeights.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::ServerReaderWriter;
using grpc::Status;
using params::Parameters;
using params::WeightsPasser;
//using params::WeightsToClient;
//using params::WeightsToServer;

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

//class that the server uses to do the do
class WeightsPasserImpl final : public WeightsPasser::Service {
public:
    WeightsPasserImpl() {
        serverNetwork = std::make_shared<Network>();
    }

    //bidirectional stream method (come back to later)
    /*Status sendWeights(ServerContext* context, 
                ServerReaderWriter<Parameters, Parameters>* serverStream) override {
        
         //parameters received from the client
        Parameters readParams; //used to read in parameters from clients
        Parameters writeParams;
        std::stringstream serverWeights;

        while (serverStream->Read(&readParams)) {

            std::unique_lock<std::mutex> lock(serverLock);
            for (const Parameters& param : clientParams) {

                //remove later--------------------
                std::fstream temp;
                temp.open("temp.txt", std::ios::out);
                temp << "it do";
                temp.close();
                //--------------------------------

                loadWeights(param);
                writeToFile("serverWeights.txt"); //remove later
                runModel();
                writeToFile("newServerWeights.txt"); //remove later

                torch::save(serverNetwork, serverWeights);
                //pack serverWeights into a params::Parameters
                //writeParams.set_parameters(serverWeights.str());
                //writeParams.set_tensor_type("Linear");
                //serverStream->Write(writeParams);
            }
            clientParams.push_back(readParams);
        }

        return Status::OK;
    }*/

    //server-side streaming method (one step at a time)
    Status sendWeights(ServerContext* context,
                        const Parameters* clientParams,
                        ServerWriter<Parameters>* writer) override {
        std::stringstream paramStream;
        Parameters returnParams;
        //load the weights from the client
        loadWeights(*clientParams);
        writeToFile("serverWeights.txt");

        //evaluate the model
        runModel();
        writeToFile("newServerWeights.txt");

        //write the weights back to the client
        torch::save(serverNetwork, paramStream);
        returnParams.set_parameters(paramStream.str());
        returnParams.set_tensor_type(clientParams->tensor_type());
        writer->Write(returnParams);
        return Status::OK;
    }

    //--------------------------------------------------------------------------
    //old read from client method
    /*Status sendWeights(ServerContext* context, const WeightsToServer* clientWeights,
                        WeightsToClient* serverWeights) override {
        std::string prefix("Test ");
        serverWeights->set_reply(prefix + clientWeights->tensor_type());

        //call a method for loading the weights into a model
        loadWeights(clientWeights);
        writeToFile("serverWeights.txt");

        runModel();
        writeToFile("newServerWeights.txt");

        return Status::OK;
    }
    

    void loadWeights(const WeightsToServer* clientWeights) {
        std::stringstream weights;
        weights << clientWeights->parameters();

        torch::load(Net, weights);
    }*/
    //--------------------------------------------------------------------------
    void loadWeights(const Parameters& clientParams) {
        std::stringstream weights;
        weights << clientParams.parameters();

        torch::load(serverNetwork, weights);
    }

    /*-------remove later-------*/
    void writeToFile(std::string fileName) {
        std::fstream writeTo;

        writeTo.open(fileName, std::ios::out);
        writeTo << serverNetwork->parameters();
        writeTo.close();
    }

    void runModel() {
        auto data_loader = torch::data::make_data_loader(
            torch::data::datasets::MNIST("../mnist").map(torch::data::transforms::Stack<>()), 64
        );

        torch::optim::SGD optimizer(serverNetwork->parameters(), 0.01);

        for (size_t epoch = 1; epoch <= 2; epoch++) {
            size_t batch_index = 0;

            for (auto& batch : *data_loader) {
                optimizer.zero_grad();

                serverNetwork->prediction = serverNetwork->forward(batch.data);
                serverNetwork->loss = torch::nll_loss(serverNetwork->prediction, batch.target);
                serverNetwork->loss.backward();

                optimizer.step();
            }
        }
    }

private:
    //Network Net;
    std::vector<Parameters> clientParams;
    std::shared_ptr<Network> serverNetwork;
    std::mutex serverLock;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    WeightsPasserImpl serverService;
    int num;

    /*--------------------figure out what these do later---------------------*/
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;

    //make a lister address
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials(), &num);
    //set "serverService" to be the instance that communication is going through
    //in this case it's a synchronous service
    builder.RegisterService(&serverService);
    //now actually assemble the service
    std::unique_ptr<Server> server(builder.BuildAndStart());
    //server = builder.BuildAndStart();
    std::cout << "Server listening on: " << server_address << std::endl;
    std::cout << "AddListeningPort returns: " << num << std::endl;
    server->Wait();
}

int main (int argc, char* argv[]) {
    RunServer();

    return 0;
}
