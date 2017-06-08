#include "abstractframeconsumer.h"

AbstractFrameConsumer::AbstractFrameConsumer()
{
	frameProducer = nullptr;
}

void AbstractFrameConsumer::consume(AbstractFrameProducer& producer)
{
	this->frameProducer = &producer;
	connect(frameProducer, SIGNAL(frameProduced(cv::Mat&)), this, SLOT(frameProduced(cv::Mat&)));
}

void AbstractFrameConsumer::frameProduced(cv::Mat &frame)
{
	onNextFrameConsumed(frame);
}

void AbstractFrameConsumer::stopConsuming()
{
	disconnect(frameProducer, SIGNAL(frameProduced(cv::Mat&)), this, SLOT(frameProduced(cv::Mat&)));
	this->frameProducer = 0;
}
