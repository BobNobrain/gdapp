#include "keyposegesturedescriptor.h"

KeyPoseGestureDescriptor::KeyPoseGestureDescriptor(unsigned int N)
{
	this->N = N;
	queueStart = 0;
	poses = new int[N];
	for (unsigned i = 0; i < N; i++)
		poses[i] = -1;
	this->isAccumulator = isAccumulator;
}

bool KeyPoseGestureDescriptor::appendPose(AbstractPoseDescriptor *keyPoseCandidate, float accuracy)
{
	// TODO: if i really need to call GL here?
	int poseIndex = GestureLibrary::matchPose(*keyPoseCandidate, accuracy);
	if (poseIndex != -1)
	{
		// key pose found
		pushToQueue(poseIndex);
		return true;
	}
	return false;
}

void KeyPoseGestureDescriptor::pushToQueue(int next)
{
	poses[queueStart] = next;
	++queueStart;
	if (queueStart >= N)
		queueStart = 0;
}
int KeyPoseGestureDescriptor::getPoseAt(unsigned int index)
{
	unsigned realIndex = queueStart + index;
	realIndex %= N;
	return poses[realIndex];
}

KeyPoseGestureDescriptor::~KeyPoseGestureDescriptor()
{
	delete[] poses;
}
