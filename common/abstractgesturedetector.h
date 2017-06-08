#ifndef ABSTRACTGESTUREDETECTOR_H
#define ABSTRACTGESTUREDETECTOR_H

#include <QObject>
#include "basicmodule.h"

class AbstractGestureDetector : public BasicModule
{
	Q_OBJECT

public:
	AbstractGestureDetector();

signals:
	void gestureDetected(int gestureId);

protected:
	/**
	 * @brief This method is called when a particular gesture is detected.
	 * It emits the GESTURE_DETECTED signal.
	 * @param gestureId - the id of the gesture in the library
	 */
	void onGestureDetected(int gestureId);
};

#endif // ABSTRACTGESTUREDETECTOR_H
