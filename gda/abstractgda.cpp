#include "abstractgda.h"

AbstractGDA::AbstractGDA()
{
	matchingAccuracy = 1.0;
}

void AbstractGDA::onGestureCandidate(AbstractGestureDescriptor &candidate)
{
	int detected = GestureLibrary::matchGesture(candidate);
	if (detected != -1)
	{
		this->onGestureDetected(detected);
	}
}
