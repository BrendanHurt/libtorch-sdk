#include <iostream>
#include <fstream>
#include <string>
#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>
#include "proto/modelParams.pb.h"

int main(int argc, char* argv[]) {
    params::modelParams outputParams;

    
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
        
        //defining the layers
        torch::nn::Linear layer1{nullptr}, layer2{nullptr}, output{nullptr};
    };

    //create a new network
    auto net = std::make_shared<Network>();

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
            torch::Tensor prediction = net->forward(batch.data);
            //compute a loss bvalue to judge the prediction of the model
            torch::Tensor loss = torch::nll_loss(prediction, batch.target);
            //compute grandients of the loss with respect to the parameters of the model
            loss.backward(); //back propogation
            //update the parameters based on the calculated gradients
            optimizer.step();
            //output the loss and checkpoint of every hundred batches
            if (++batch_index % 100 == 0) {
                std::cout << "Epochs: " << epoch << " | Batch: " 
                    << batch_index << " | Loss: " << loss.item<float>() << std::endl;
            }
        }
    }
    
    //testing saving the weights
    /*std::vector<char> buffer = torch::pickle_save(net->layer2->weight);
    std::ofstream output;
    output.open("paramsOut.txt");
    output << buffer;
    output.close();*/
    

    //testing the parameters
    char temp = 'A';
    outputParams.set_parameters(std::string(temp, sizeof(char)));

    //write the serialized data to a file
    std::fstream output(argv[1], std::ios::out | std::ios::trunc | std::ios::binary);
    if (!outputParams.SerializeToOstream(&output)) {
        std::cerr << "Failed to write to file" << std::endl;
        return -1;
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}