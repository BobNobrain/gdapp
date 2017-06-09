#include "abstractgda.h"

AbstractGDA::AbstractGDA(std::string glibFilename)
    : emitter(this)
{
	matchingAccuracy = 0.8F;
	glib.load(glibFilename);
}

AbstractGDA::~AbstractGDA() {}

AbstractGestureDetector* AbstractGDA::getDetector()
{
	return &emitter;
}

std::string& AbstractGDA::getGestureName(int gestureId)
{
	return glib.getGestureName(gestureId);
}

void AbstractGDA::onGestureCandidate(AbstractGestureDescriptor* candidate)
{
	int detected = classifyGesture(candidate);
	if (detected != -1)
	{
		emitter.emitGestureDetected(detected);
	}
}

int AbstractGDA::classifyGesture(AbstractGestureDescriptor *gesture)
{
	return glib.match(gesture, matchingAccuracy);
}

std::string& AbstractGDAEmitter::getGestureName(int gestureId)
{
	if (parent == nullptr)
		return getErrorName();
	return parent->getGestureName(gestureId);
}
