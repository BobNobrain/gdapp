#include "keyposegesturedescriptor.h"

KeyPoseGestureDescriptor::KeyPoseGestureDescriptor(unsigned int N)
{
	this->N = N;
	queueStart = 0;
	poses = new int[N];
	for (unsigned i = 0; i < N; i++)
		poses[i] = -1;
}

KeyPoseGestureDescriptor::~KeyPoseGestureDescriptor()
{
	delete[] poses;
}

bool KeyPoseGestureDescriptor::appendPose(int poseIndex)
{
	if (poseIndex != -1)
	{
		// key pose found
		pushToQueue(poseIndex);
		return true;
	}
	return false;
}

float KeyPoseGestureDescriptor::similarTo(AbstractGestureDescriptor *templateDesctiptor)
{
	/*
	 * NOTE: when we call similarTo, `this` descriptor is always accumulator. It means the following:
	 * - `this` contains more or equal poses than template descriptor;
	 * - `templateDescriptor->queueStart` is always at 0, and it means that its getPoseAt(i) == its poses[i]
	 */
	KeyPoseGestureDescriptor* another = dynamic_cast<KeyPoseGestureDescriptor*> (templateDesctiptor);
	if (another == nullptr)
		return 0.0F; // no match at all because of different types
	// TODO: use more robust algorithm
	int matches = 0;
	for (unsigned i = another->N - 1; i >= 0; i--)
	{
		int p_this = getPoseAt(i);
		int p_model = another->poses[i];
		if (p_this == p_model)
			++matches;
	}
	// matches count to total possible matches count
	return matches * 1.0F / another->N;
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

void KeyPoseGestureDescriptor::resetPointer()
{
	queueStart = 0;
}

class KeyPoseGDFactory: GestureDescriptorFactory
{
public:
	KeyPoseGDFactory()
	{
		AbstractGestureDescriptor::registerType("keypose", this);
	}

	AbstractGestureDescriptor* create(const json &params)
	{
		unsigned int n = (unsigned int) params["data"].size();
		KeyPoseGestureDescriptor* result = new KeyPoseGestureDescriptor(n);
		if (params.find("data") != params.end())
		{
			json data_arr = params["data"];
			for (int n: data_arr)
			{
				result->appendPose(n);
			}
		}
		return result;
	}
};
