#include "exampleClient.hpp"

exampleClient::exampleClient() : numEpochs(2), batchSize(64) {
    net = std::make_shared<Network>();
}

exampleClient::~exampleClient() {
    net.reset();
}

//handles the fit
//  change kBatchSize to be a client attribute?
void exampleClient::train() {
    torch::nn::CrossEntropyLossImpl criterion;
    torch::Tensor loss;

    auto dataset = torch::data::datasets::MNIST(
            "../mnist",
            torch::data::datasets::MNIST::Mode::kTrain
        )
        .map(torch::data::transforms::Normalize<>(0.5,0.5))
        .map(torch::data::transforms::Stack<>()
    );
    auto train_set = torch::data::make_data_loader(
        std::move(dataset),
        torch::data::DataLoaderOptions().batch_size(batchSize)
    );
    
    torch::optim::SGD optimizer(net->parameters(), 0.001);

    for (size_t currEpoch = 0; currEpoch < numEpochs; ++currEpoch) {
        size_t batch_index = 0;
        for (auto &batch : *train_set) {
            optimizer.zero_grad();
            loss = criterion.forward(net->forward(batch.data), batch.target);
            loss.backward();
            optimizer.step();
            if (!(++batch_index % 100)) {
                std::cout << "Epochs: " << currEpoch << " | Batch: " 
                    << batch_index << " | Loss: " << loss.item<float>() << std::endl;
            }
        }
    }
}

std::pair<float, float> exampleClient::test() {
    torch::Tensor outputs, predicted;
    float loss(0.0f), accuracy(0.0f);
    int correct(0), total(0);

    auto dataset = torch::data::datasets::MNIST(
            "../mnist",
            torch::data::datasets::MNIST::Mode::kTest
        )
        .map(torch::data::transforms::Normalize<>(0.5,0.5))
        .map(torch::data::transforms::Stack<>()
    );
    auto test_set = torch::data::make_data_loader(
        std::move(dataset),
        torch::data::DataLoaderOptions().batch_size(batchSize)
    );
    
    torch::NoGradGuard();
    //kinda doubtful of the predicted & correct lines, worry about it later
    for (auto &batch : *test_set) {
        outputs = net->forward(batch.data);

        loss += torch::cross_entropy_loss(outputs, batch.target).item<float>();

        //maybe put in a loop to make sure the max is getting got?
        predicted = std::get<1>(torch::max(outputs, int64_t(1), false));

        total += batch.data.size(0);

        //doesn't seem to be working, returning an accuracy of 0
        if (predicted.sum().item<int>() == batch.target.sum().item<int>()) {
            
            ++correct;
            std::cout << "it was right! correct: " << correct << std::endl;
        }
    }
    accuracy = correct / total;
    return std::pair<float, float>(loss, accuracy);
}
