#include "image227keyposedescriptor.h"
#include <iostream>
#include <opencv2/imgproc.hpp>

Image227KeyPoseDescriptor::Image227KeyPoseDescriptor(cv::Mat& videoframe)
{
	// reshape the frame to 227x227 size
	int w = videoframe.size().width, h = videoframe.size().height;
	cv::Rect crop_rect;
	if (w > h)
	{
		int mw = (w - h) / 2;
		crop_rect.x = mw;
		crop_rect.y = 0;
		crop_rect.width = h;
		crop_rect.height = h;
	}
	else
	{
		int mh = (h - w) / 2;
		crop_rect.x = 0;
		crop_rect.y = mh;
		crop_rect.width = w;
		crop_rect.height = w;
	}

	data = videoframe(crop_rect);
	cv::resize(data, data, cv::Size(227, 227));
}

Image227KeyPoseDescriptor::~Image227KeyPoseDescriptor() {}

cv::Mat& Image227KeyPoseDescriptor::getData()
{
	return data;
}

float Image227KeyPoseDescriptor::similarTo(AbstractPoseDescriptor *templatePose)
{
	// this method should not be called
	std::cerr << "Warning: Image227KeyPoseDescriptor::similarTo call should not be performed!" << std::endl;
	return 0.0F;
}
