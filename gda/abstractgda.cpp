#include "abstractgda.h"

AbstractGDA::AbstractGDA(std::string glibFilename)
{
	matchingAccuracy = 0.8F;
	glib.load(glibFilename);
}

AbstractGDA::~AbstractGDA() {}

AbstractGestureDetector* AbstractGDA::getDetector()
{
	return &emitter;
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
