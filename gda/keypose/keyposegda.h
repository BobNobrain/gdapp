#ifndef KEYPOSEGDA_H
#define KEYPOSEGDA_H

#include <QObject>
#include "gda/abstractgda.h"
#include "abstractposedescriptor.h"
#include "keyposegesturedescriptor.h"

class KeyPoseGDA : public AbstractGDA
{
	Q_OBJECT
public:
	KeyPoseGDA(std::__cxx11::string glibFilename, unsigned int maxPosesPerGesture);
	~KeyPoseGDA();

	float poseMatchingAccuracy;

protected:
	void onKeyPoseCandidate(AbstractPoseDescriptor* candidate);

	virtual int classifyKeyPose(AbstractPoseDescriptor* pose) = 0;

	KeyPoseGestureDescriptor* accumulator;
};

#endif // KEYPOSEGDA_H
