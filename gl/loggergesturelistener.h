#ifndef LOGGERGESTURELISTENER_H
#define LOGGERGESTURELISTENER_H

#include <QObject>
#include <iostream>
#include "common/abstractgesturelistener.h"

class LoggerGestureListener : public AbstractGestureListener
{
	Q_OBJECT
public:
	LoggerGestureListener(std::ostream* os);
	~LoggerGestureListener();

protected:
	virtual void onGestureDetected(int gestureId) override;

	std::ostream* outs;
};

#endif // LOGGERGESTURELISTENER_H
