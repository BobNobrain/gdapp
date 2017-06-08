#ifndef ABSTRACTFRAMECONSUMER_H
#define ABSTRACTFRAMECONSUMER_H

#include <QObject>
#include <opencv/cv.h>
#include "basicmodule.h"
#include "abstractframeproducer.h"

class AbstractFrameConsumer : public BasicModule
{
	Q_OBJECT
public:
	AbstractFrameConsumer();

	/**
	 * @brief Links the algorithm to a source of video frames to consume. GDA is not responsible for freeing it.
	 * When linked, consumes every produced frame (see onNextFrameConsumed).
	 * @param producer - the source of video frames
	 */
	void consume(AbstractFrameProducer* producer);

	/**
	 * @brief Stops consuming frames from FrameProducer and disconnects from it.
	 * Method does not free the FrameProducer, but nulls link for it.
	 */
	void stopConsuming();

protected:
	/**
	 * @brief Implement your main algorithm logic inside this method.
	 * It is invoked every time when new video frame is consumed
	 * @param nextFrame - the video frame content itself
	 */
	virtual void onNextFrameConsumed(cv::Mat& nextFrame) = 0;

private slots:
	void frameProduced(cv::Mat& frame);

private:
	AbstractFrameProducer* frameProducer;
};

#endif // ABSTRACTFRAMECONSUMER_H
