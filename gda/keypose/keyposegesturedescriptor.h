#ifndef KEYPOSEGESTUREDESCRIPTOR_H
#define KEYPOSEGESTUREDESCRIPTOR_H

#include "gda/common/abstractgesturedescriptor.h"
#include "abstractposedescriptor.h"

class KeyPoseGestureDescriptor : public AbstractGestureDescriptor
{
public:
	KeyPoseGestureDescriptor(unsigned int N);
	~KeyPoseGestureDescriptor();

	/**
	 * @brief Should be called on every PoseDescriptor obtained. Will internally check if
	 * it's a key pose and modify itself.
	 * @param The obtained descriptor.
	 * @return Whether the gesture descriptor was modified
	 */
	virtual bool appendPose(AbstractPoseDescriptor* keyPoseCandidate, float accuracy);

private:
	int* poses;
	unsigned int queueStart;
	unsigned int N;
	void pushToQueue(int next);
	int getPoseAt(unsigned int index);
};

#endif // KEYPOSEGESTUREDESCRIPTOR_H
