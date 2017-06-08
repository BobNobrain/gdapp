#include "abstractgesturedetector.h"

AbstractGestureDetector::AbstractGestureDetector()
{
}

void AbstractGestureDetector::onGestureDetected(int gestureId)
{
	emit gestureDetected(gestureId);
}
