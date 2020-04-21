#include <iostream>
#include "DataHandler.h"
#include "OutputFunctions.h"
#include "NeuralNetwork.h"

int main() {

    mnist::DataHandler dataHandler;
    dataHandler.readTrain(
            "/home/dimedrol/Desktop/mnist/train-images-idx3-ubyte",
            "/home/dimedrol/Desktop/mnist/train-labels.idx1-ubyte");

    NeuralNetwork network({static_cast<unsigned long>(dataHandler.getWidth() * dataHandler.getHeight()), 10, 10}, 0.1);

    int epochs = 100;
    for (int i = 0; i < epochs; i++) {
        network.BackPropagation(dataHandler.getTrainImage(i), dataHandler.getTrainLabelVectorized(i));
        std::cout << "Back propagation " << i << " complete" << std::endl;
    }

    std::cout << "Learning complete. Starting tests..." << std::endl;

    for (int i = epochs; i < epochs + 50; i++) {
        std::cout << "Attempt " << i << ". ";
        dataHandler.printTrainImage(i);
        auto output = network.FeedForward(dataHandler.getTrainImage(i));

        double max_activation = -1.0;
        int response_digit = -1;
        for (int j = 0; j < output.size(); j++)
            if (output[j] > max_activation) {
                max_activation = output[j];
                response_digit = j;
            }

        std::cout << "Response digit is " << response_digit << std::endl;
    }

    return 0;
}
