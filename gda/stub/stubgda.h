#ifndef STUBGDA_H
#define STUBGDA_H

#include <QObject>
#include <opencv/cv.h>
#include "gda/abstractgda.h"

class StubGDA: public AbstractGDA
{
	Q_OBJECT
public:
	StubGDA(std::string glibFilename, float prob = 0.1F);
	~StubGDA();

	void onNextFrameConsumed(cv::Mat& nextFrame) override;
	int classifyGesture(AbstractGestureDescriptor *gesture) override;

	float generationProbability;
};

#endif // STUBGDA_H
