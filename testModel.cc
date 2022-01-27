#include <iostream>
#include <fstream>
#include <string>
#include "proto/sdk_transport.pb.h"
//#include "client.cc"
#include "client.hpp"
#include "typing.h"

//torch
#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>

//----------------------------------------------------------------------------
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
    
    torch::Tensor fit;
    torch::Tensor loss;
    //defining the layers
    torch::nn::Linear layer1{nullptr}, layer2{nullptr}, output{nullptr};
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void writeToFile(std::string fileName, std::shared_ptr<Network> net) {
    std::fstream writeTo;

    writeTo.open(fileName, std::ios::out);
    writeTo << net->loss;//net->parameters();
    writeTo.close();
}

void runModel(std::shared_ptr<Network> net) {
    int kNoiseSize = 1;
    int kBatchSize = 64;
    int batches_per_epoch = 938;
    int kNumberOfEpochs = 10;

    auto data_loader = torch::data::make_data_loader(
        torch::data::datasets::MNIST("../mnist").map(torch::data::transforms::Stack<>()), /*batch size*/ 64);

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
            net->fit = net->forward(batch.data);
            //compute a loss bvalue to judge the fit of the model
            net->loss = torch::nll_loss(net->fit, batch.target);
            //compute grandients of the loss with respect to the parameters of the model
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
}

void disconnect_test(Client& client) {
    //
}

void parameters_test(Client& client, const std::shared_ptr<Network> net) { 
    std::fstream writer;
    std::vector<std::string> layers;
    std::stringstream buffer;
    torch::save(net->layer1, buffer);
    layers.push_back(buffer.str());
    torch::save(net->layer2, buffer);
    layers.push_back(buffer.str());
    torch::save(net->output, buffer);
    layers.push_back(buffer.str());
    client.set_parameters(layers);

    writer.open("logs/userParams.txt", std::ios::out);
    for (int i = 0; i < layers.size(); i++) {
        writer << layers[i];
        writer << "\n\n";
    }
    writer.close();
    //client.test_params();
}

void fit_test(Client& client, const std::shared_ptr<Network> net) {
    std::map<std::string, typing::Scalar> my_map;
    typing::Scalar my_scalar;
    my_scalar._string = "string";
    std::stringstream buffer;
    std::fstream writer;

    my_map.emplace("here", my_scalar);
    client.set_fit(net->fit, 1000, my_map);

    torch::save(net->fit, buffer);
    writer.open("logs/userFit.txt", std::ios::out);
    writer << buffer.str();
    writer.close();
    //client.test_fit();
}

void evaluate_test(Client& client, const std::shared_ptr<Network> net) {
    std::map<std::string, typing::Scalar> my_map;
    typing::Scalar my_scalar;
    my_scalar._string = "string";
    my_map.emplace("here", my_scalar);

    client.set_evaluate(net->loss.item<float>(), 1000, my_map);
    //client.test_eval();
}

void properties_test(Client& client) {
    std::map<std::string, typing::Scalar> my_map;
    typing::Scalar my_scalar;
    my_scalar._string = "string";
    my_map.emplace("here", my_scalar);
    client.set_properties(my_map);
    //add a test method?
}

//================================================================================
int main(int argc, char* argv[]) {
    std::string targetString = "localhost:50051";
    std::shared_ptr<Network> net = std::make_shared<Network>();
    std::stringstream buffer;

    //make the service
    Client client(
        grpc::CreateChannel(targetString, grpc::InsecureChannelCredentials()));

    //1. run the model
    runModel(net);

    //2. test the client container
    //disconnect_test(client);
    parameters_test(client, net);
    fit_test(client, net);
    evaluate_test(client, net);
    properties_test(client);

    //3. test the streaming method
    client.transport_model();

    //kinda just an end marker for now
    typing::Scalar a_scalar;
    a_scalar._bool = true;
    a_scalar._bytes = "bytes";
    a_scalar._double = 1.5;
    a_scalar._int = 2;
    a_scalar._string = "string";
    flower_sdk::Scalar temp = client.to_flower(a_scalar);
    std::cout << temp.double_() << " "
                << temp.sint64() << " "
                << temp.bool_() << " "
                << temp.string() << " "
                << temp.bytes() << std::endl;
    
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}