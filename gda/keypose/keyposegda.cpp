#include "keyposegda.h"

KeyPoseGDA::KeyPoseGDA(std::string glibFilename, unsigned int maxPosesPerGesture): AbstractGDA(glibFilename)
{
	accumulator = new KeyPoseGestureDescriptor(maxPosesPerGesture);
	poseMatchingAccuracy = 0.8F;
}

KeyPoseGDA::~KeyPoseGDA()
{
	delete accumulator;
}

void KeyPoseGDA::onKeyPoseCandidate(AbstractPoseDescriptor *candidate)
{
	int kpClass = classifyKeyPose(candidate);
	if (accumulator->appendPose(kpClass))
	{
		onGestureCandidate(accumulator);
	}
}
