#ifndef IMAGE227KEYPOSEDESCRIPTOR_H
#define IMAGE227KEYPOSEDESCRIPTOR_H

#include <opencv/cv.h>
#include "gda/keypose/abstractposedescriptor.h"

class Image227KeyPoseDescriptor: public AbstractPoseDescriptor
{
public:
	Image227KeyPoseDescriptor(cv::Mat& videoframe);
	~Image227KeyPoseDescriptor();

	float similarTo(AbstractPoseDescriptor *templatePose) override;

	cv::Mat& getData();

private:
	cv::Mat data;
};

#endif // IMAGE227KEYPOSEDESCRIPTOR_H
