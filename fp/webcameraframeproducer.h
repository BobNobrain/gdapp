#ifndef WEBCAMERAFRAMEPRODUCER_H
#define WEBCAMERAFRAMEPRODUCER_H

#include <QObject>
#include <opencv/highgui.h>
#include "common/abstractframeproducer.h"

class WebCameraFrameProducer: public AbstractFrameProducer
{
	Q_OBJECT
public:
	WebCameraFrameProducer(int camid = 0);
	~WebCameraFrameProducer();

	void startProducing();

private:
	CvCapture* webcam;
	IplImage* lastFrameIpl;
};

#endif // WEBCAMERAFRAMEPRODUCER_H
