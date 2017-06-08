#include "abstractgesturelistener.h"

AbstractGestureListener::AbstractGestureListener()
{
	detector = nullptr;
}

void AbstractGestureListener::listen(AbstractGestureDetector *d)
{
	if (detector != 0)
	{
		disconnect(detector, SIGNAL(gestureDetected(int)), this, SLOT(gestureDetected(int)));
	}
	detector = d;
	if (d != 0)
	{
		connect(detector, SIGNAL(gestureDetected(int)), this, SLOT(gestureDetected(int)));
	}
}

void AbstractGestureListener::gestureDetected(int gestureId)
{
	onGestureDetected(gestureId);
}
