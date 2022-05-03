#include <torch/torch.h>
#include <torch/script.h>
#include <dirent.h>
#include <ATen/ATen.h>

class exampleClient {
    public:
    exampleClient();
    ~exampleClient();

    void get_parameters() {
        //look up torch::parameters
    }

    void set_parameters() {}
    void train();
    std::pair<float, float> test();

    private:
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

    //add the maps later
    torch::Tensor weights;
    int batchSize;
    int numEpochs;
    std::shared_ptr<Network> net;
};