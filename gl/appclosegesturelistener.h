#ifndef APPCLOSEGESTURELISTENER_H
#define APPCLOSEGESTURELISTENER_H

#include "common/abstractgesturelistener.h"

class AppCloseGestureListener: public AbstractGestureListener
{
public:
	AppCloseGestureListener(int gestId, bool twice);
	~AppCloseGestureListener();

	virtual void onGestureDetected(int gestureId) override;

protected:
	bool repeat;
	int gest;

private:
	bool done_once;
};

#endif // APPCLOSEGESTURELISTENER_H
