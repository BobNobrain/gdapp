#ifndef CAFFENEURALNET_H
#define CAFFENEURALNET_H

#include <opencv2/dnn.hpp>
#include "neuralnet.h"

using namespace cv;
using namespace cv::dnn;

class CaffeNeuralNet : public NeuralNet
{
public:
	CaffeNeuralNet(std::string weightsFilename, std::string structureFile, unsigned int nClasses);
	~CaffeNeuralNet();

	int forward(cv::Mat& input, double& classProb) override;
	unsigned int getNClasses() override;

private:
	dnn::Net net;
	unsigned int nc;
};

#endif // CAFFENEURALNET_H
