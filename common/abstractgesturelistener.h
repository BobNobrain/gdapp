#ifndef ABSTRACTGESTURELISTENER_H
#define ABSTRACTGESTURELISTENER_H

#include <QObject>
#include "basicmodule.h"
#include "abstractgesturedetector.h"

class AbstractGestureListener: public BasicModule
{
	Q_OBJECT

public:
	AbstractGestureListener();

	void listen(AbstractGestureDetector* algo);

	~AbstractGestureListener();

protected:
	virtual void onGestureDetected(int gestureId) = 0;

private slots:
	void gestureDetected(int gestureId);

private:
	AbstractGestureDetector* detector;

};

#endif // ABSTRACTGESTURELISTENER_H
