#include "displayframeconsumer.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

DisplayFrameConsumer::DisplayFrameConsumer(std::string wname)
{
	this->wname = wname;
	cvNamedWindow(wname.c_str());
}

DisplayFrameConsumer::~DisplayFrameConsumer()
{
	cv::destroyWindow(wname);
}

void DisplayFrameConsumer::onNextFrameConsumed(cv::Mat& nextFrame)
{
	cv::imshow(wname, nextFrame);
}

class DisplayFrameConsumerFactory: public ModuleFactory
{
public:
	DisplayFrameConsumerFactory()
	{
		BasicModule::registerModule("displayer", this);
	}

	BasicModule* create(const nlohmann::json &params)
	{
		std::string wname = "(displayer)";
		if (params.find("window_name") != params.end())
			wname = params["window_name"];
		return new DisplayFrameConsumer(wname);
	}
};

static DisplayFrameConsumerFactory global_DisplayFrameConsumerFactory;
