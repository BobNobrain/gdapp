#ifndef DISPLAYFRAMECONSUMER_H
#define DISPLAYFRAMECONSUMER_H

#include <QObject>
#include <opencv/cv.h>
#include "common/abstractframeconsumer.h"

class DisplayFrameConsumer: public AbstractFrameConsumer
{
	Q_OBJECT
public:
	DisplayFrameConsumer(std::string wname);
	~DisplayFrameConsumer();

	void onNextFrameConsumed(cv::Mat& nextFrame) override;

private:
	std::string wname;
};

#endif // DISPLAYFRAMECONSUMER_H
