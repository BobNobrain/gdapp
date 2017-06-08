#ifndef ABSTRACTGDA_H
#define ABSTRACTGDA_H

#include <QObject>
#include "common/abstractframeconsumer.h"
#include "common/abstractgesturedetector.h"
#include "gda/common/abstractgesturedescriptor.h"

class AbstractGDA: public AbstractFrameConsumer, public AbstractGestureDetector
{
public:
	AbstractGDA();
	~AbstractGDA();

protected:
	/**
	 * @brief Call this method every time you obtained a gesture descriptor.
	 * It will call internally GestureLibrary::match to chech if the candidate
	 * is a predefined gesture. If a match found, it will emit signal
	 * GESTURE_DETECTED internally.
	 * @param candidate - the obtained descriptor that can be a predefined gesture.
	 */
	void onGestureCandidate(AbstractGestureDescriptor& candidate);

	/**
	 * @brief Variable is used to compare gesture candidates with gesture models in library
	 */
	float matchingAccuracy;
};

#endif // ABSTRACTGDA_H
