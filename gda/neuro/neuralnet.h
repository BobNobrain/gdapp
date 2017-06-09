#ifndef NEURALNET_H
#define NEURALNET_H

#include <opencv/cv.h>

class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();

	virtual int forward(cv::Mat &input, double& classProb) = 0;
	virtual unsigned int getNClasses() = 0;
};

#endif // NEURALNET_H
