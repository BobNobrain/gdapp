#ifndef NEUROGDA_H
#define NEUROGDA_H

#include <opencv/cv.h>
#include "gda/keypose/keyposegda.h"
#include "neuralnet.h"

class NeuroGDA: public KeyPoseGDA
{
	Q_OBJECT
public:
	NeuroGDA(std::string glibFilename, unsigned int maxPosesPerGesture);
	~NeuroGDA();

	virtual void onNextFrameConsumed(cv::Mat& nextFrame) override;
	virtual int classifyKeyPose(AbstractPoseDescriptor *pose) override;

	friend class NeuroGDAFactory;

private:
	NeuralNet* net;
};

#endif // NEUROGDA_H
