#ifndef ABSTRACTFRAMEPRODUCER_H
#define ABSTRACTFRAMEPRODUCER_H

#include <opencv/cv.h>
#include <QObject>
#include "common/basicmodule.h"

class AbstractFrameProducer: public BasicModule
{
	Q_OBJECT

public:
	AbstractFrameProducer();
	~AbstractFrameProducer();

	/**
	 * @brief getFrameWidth
	 * @return width of the produced frames
	 */
	size_t getFrameWidth();
	/**
	 * @brief getFrameHeight
	 * @return height of the produced frames
	 */
	size_t getFrameHeight();

	/**
	 * @brief Launches some operation that will produce the frames. Blocking (?).
	 */
	virtual void startProducing() = 0;

signals:
	/**
	 * @brief Notifies that a new frame was produced
	 * @param frame - the produced frame
	 */
	void frameProduced (cv::Mat& frame);

protected:

	/**
	 * @brief Call this function every time a new video frame is produced.
	 * Emits frameProduced signal internally.
	 * @param frame - the newly produced frame
	 */
	void onFrameGenerated(cv::Mat& frame);

	/**
	 * @brief Use this field as a mat that stores obtained image
	 */
	cv::Mat lastFrame;
};

#endif // ABSTRACTFRAMEPRODUCER_H
