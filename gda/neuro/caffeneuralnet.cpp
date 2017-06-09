#include "caffeneuralnet.h"
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void getMaxClass(dnn::Blob &probBlob, int *classId, double *classProb)
{
	Mat probMat = probBlob.matRefConst().reshape(1, 1);
	Point classNumber;
	minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
	*classId = classNumber.x;
}

CaffeNeuralNet::CaffeNeuralNet(std::string weightsFilename, std::string structureFile, unsigned int nClasses)
{
	Ptr<dnn::Importer> importer;
	nc = nClasses;
	try
	{
		importer = dnn::createCaffeImporter((cv::String) structureFile, (cv::String) weightsFilename);
		importer->populateNet(net);
		importer.release();
	}
	catch (const cv::Exception &err)
	{
		std::cerr << err.msg << std::endl;
	}
}

CaffeNeuralNet::~CaffeNeuralNet() {}

int CaffeNeuralNet::forward(Mat& input, double& classProb)
{
	dnn::Blob inputBlob = dnn::Blob(input);
	net.setBlob(".data", inputBlob);
	net.forward();
	dnn::Blob out = net.getBlob("prob");
	int classId;
	double cprob;
	getMaxClass(out, &classId, &cprob);
	classProb = cprob;
	return classId;
}

unsigned int CaffeNeuralNet::getNClasses()
{
	return nc;
}
