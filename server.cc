#include <iostream>
#include <fstream>
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

#include "proto/sdk_transport.grpc.pb.h"
#include "proto/sdk_transport.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;

//flower namespace elements
using namespace flower_sdk;

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
    
    torch::Tensor fit;
    torch::Tensor loss;

    //defining the layers
    torch::nn::Linear layer1{nullptr}, layer2{nullptr}, output{nullptr};
};

//class that the server uses to do the do
class FlowerServiceSDKImpl final : public FlowerServiceSDK::Service {
public:
    FlowerServiceSDKImpl() {
        server_network = std::make_shared<Network>();

        /*disconnect_msg = new ClientMessage_Disconnect();
        parameters_res_msg = new ClientMessage_ParametersRes();
        fit_res_msg = new ClientMessage_FitRes();
        evaluate_res_msg = new ClientMessage_EvaluateRes();
        properties_res_msg = new ClientMessage_PropertiesRes();*/
    }
    /*~FlowerServiceSDKImpl() {
        //have server containers?

        //clear up client containers
        delete disconnect_msg;
        delete parameters_res_msg;
        delete fit_res_msg;
        delete evaluate_res_msg;
        delete properties_res_msg;
    }*/

    /**-----------------Join-----------------
     * 
    */
    Status Join(ServerContext* context,
            ServerReaderWriter<ServerMessage, ClientMessage>* stream) override {
        ClientMessage client_msg;
        ServerMessage server_msg;
        int i = 0;
        logger.open("logs/serverLog.txt", std::ios::out);

        while (stream->Read(&client_msg)) {
            std::unique_lock<std::mutex> lock(server_lock);
            logger << "reading client message " << i << std::endl;

            if (client_msg.has_disconnect()) {
                logger << "disconnect from message " << i << std::endl;
                get_disconnect_res(client_msg.disconnect());

            } else if (client_msg.has_parameters_res()) {
                logger << "parameters from message " << i << std::endl;
                get_parameters_res(client_msg.parameters_res());

            } else if (client_msg.has_fit_res()) {
                logger << "fit from message " << i << std::endl;
                get_fit_res(client_msg.fit_res());

            } else if (client_msg.has_evaluate_res()) {
                logger << "evaluate from message " << i << std::endl;
                get_evaluate_res(client_msg.evaluate_res());

            } else if (client_msg.has_properties_res()) {
                logger << "properties from message " << i << std::endl;
                get_properties_res(client_msg.properties_res());

            } else {
                logger << "message " << i << " is empty\n";
            }
            i++;
            client_messages.push_back(client_msg);

            //just writing back an empty server message for now
            server_msg.clear_reconnect();
            server_msg.clear_get_parameters();
            server_msg.clear_fit_ins();
            server_msg.clear_evaluate_ins();
            server_msg.clear_properties_ins();
            logger << "writing a Servermessage\n";
            stream->Write(server_msg);
        }
        logger.close();        
        return Status::OK;
    }

    /////////////////////////////////////////////////////////////
    //receive client messages

    /**-----------------client disconnect-----------------*/
    void get_disconnect_res(const ClientMessage_Disconnect& disconnect_msg) {
        //figure out what to do with that
    }

    /**-----------------client parameters-----------------*/
    void get_parameters_res(const ClientMessage_ParametersRes& parameters_res) {
        writer.close();
        writer.open("logs/serverParams.txt", std::ios::out);
        writer << parameters_res.parameters().parameters(0) << std::endl;
        writer << parameters_res.parameters().parameters(1) << std::endl;
        writer << parameters_res.parameters().parameters(2) << std::endl;
        writer.close();
    }

    /**-----------------client fit-----------------*/
    void get_fit_res(const ClientMessage_FitRes& fit_res) {
        google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
        writer.close();
        writer.open("logs/serverFit.txt", std::ios::out);

        writer << fit_res.parameters().parameters(0) << std::endl;
        writer << fit_res.num_examples() << std::endl;

        for (it = fit_res.metrics().begin();
                it != fit_res.metrics().end(); it++) {
            writer << it->first << " " << it->second.string();
        }
        writer.close();
    }

    /**-----------------client evaluate-----------------*/
    void get_evaluate_res(const ClientMessage_EvaluateRes evaluate_res) {
        google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
        writer.close();
        writer.open("logs/serverEvaluate.txt", std::ios::out);

        writer << evaluate_res.num_examples() << std::endl;
        writer << evaluate_res.loss() << std::endl;

        for (it = evaluate_res.metrics().begin();
                it != evaluate_res.metrics().end(); it++) {
            writer << it->first << " " << it->second.string();
        }
        writer.close();
    }

    /**-----------------client properties-----------------*/
    void get_properties_res(const ClientMessage_PropertiesRes& properties_res) {
        google::protobuf::Map<std::string, flower_sdk::Scalar>::const_iterator it;
        writer.close();
        writer.open("logs/serverProps.txt", std::ios::out);

        for (it = properties_res.properties().begin();
                it != properties_res.properties().end(); it++) {
            writer << it->first << " " << it->second.string();
        }
        writer.close();
    }

    /////////////////////////////////////////////////////////////
    //send server messages
    void send_reconnect_msg() {}
    void send_parameters() {}
    void send_fit_ins() {}
    void send_evaluate_ins() {}
    void send_properties_ins() {}
    

private:

    /*-------remove later-------*/
    void writeToFile(std::string fileName) {
        std::fstream writeTo;

        writeTo.open(fileName, std::ios::out);
        writeTo << server_network->parameters();
        writeTo.close();
    }

    //runs the evaluation of the simple model that i've made
    void runModel() {
        auto data_loader = torch::data::make_data_loader(
            torch::data::datasets::MNIST("../mnist").map(torch::data::transforms::Stack<>()), 64
        );

        torch::optim::SGD optimizer(server_network->parameters(), 0.01);

        for (size_t epoch = 1; epoch <= 2; epoch++) {
            size_t batch_index = 0;

            for (auto& batch : *data_loader) {
                optimizer.zero_grad();

                server_network->fit = server_network->forward(batch.data);
                server_network->loss = torch::nll_loss(server_network->fit, batch.target);
                server_network->loss.backward();

                optimizer.step();
            }
        }
    }

    ////////////////////////////////////////////
    //attributes
    /*ServerMessage*                  server_msg;
    ServerMessage_Reconnect*        reconnect_msg;
    ServerMessage_GetParameters*    parameters_msg;
    ServerMessage_FitIns*           fit_msg;
    ServerMessage_EvaluateIns*      evaluate_msg;
    ServerMessage_PropertiesIns*    properties_msg;

    //containers for client messages (better way?)
    ClientMessage_Disconnect*    disconnect_msg;
    ClientMessage_ParametersRes* parameters_res_msg;
    ClientMessage_FitRes*        fit_res_msg;
    ClientMessage_EvaluateRes*   evaluate_res_msg;
    ClientMessage_PropertiesRes* properties_res_msg;*/

    std::fstream writer, logger;
    std::vector<ClientMessage> client_messages;
    std::shared_ptr<Network> server_network;
    std::mutex server_lock;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    FlowerServiceSDKImpl server_service;
    int num;

    /*--------------------figure out what these do later---------------------*/
    //grpc::EnableDefaultHealthCheckService(true);
    //grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;

    //make a lister address
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials(), &num);
    //set "serverService" to be the instance that communication is going through
    //in this case it's a synchronous service
    builder.RegisterService(&server_service);
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
