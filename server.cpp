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
using grpc::Status;
using params::weightsPasser;
using params::WeightsToClient;
using params::WeightsToServer;

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
    
    //defining the layers
    torch::nn::Linear layer1{nullptr}, layer2{nullptr}, output{nullptr};
};

//class that the server uses to do the do
class weightsPasserImpl final : public weightsPasser::Service {
public:
    weightsPasserImpl() {
        Net = std::make_shared<Network>();
    }

    Status sendWeights(ServerContext* context, const WeightsToServer* clientWeights,
                        WeightsToClient* serverWeights) override {
        std::string prefix("Test ");
        serverWeights->set_reply(prefix + clientWeights->tensor_type());

        //call a method for loading the weights into a model
        loadWeights(clientWeights);

        return Status::OK;
    }

    void loadWeights(const WeightsToServer* clientWeights) {
        std::stringstream weights;
        weights << clientWeights->parameters();
        torch::load(Net, weights);

        writeTo.open("serverWeights.txt", std::ios::out);
        writeTo << Net->parameters();
        writeTo.close();
    }

private:
    //Network Net;
    std::shared_ptr<Network> Net;
    std::fstream writeTo;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    weightsPasserImpl serverService;
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
