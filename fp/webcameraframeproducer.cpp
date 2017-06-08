#include "webcameraframeproducer.h"

WebCameraFrameProducer::WebCameraFrameProducer(int camid)
{
	webcam = cvCreateCameraCapture(CV_CAP_ANY);
	if (webcam == 0) throw "No camera can be accessed!";
}

void WebCameraFrameProducer::startProducing()
{
	while (true)
	{
		lastFrameIpl = cvQueryFrame(webcam);
		lastFrame = cv::cvarrToMat(lastFrameIpl);
		onFrameGenerated(lastFrame);
		cvWaitKey(33);
	}
}

WebCameraFrameProducer::~WebCameraFrameProducer()
{
	delete webcam;
	delete lastFrameIpl;
}


class WebCameraFrameProducerFactory: public ModuleFactory
{
public:
	WebCameraFrameProducerFactory()
	{
		BasicModule::registerModule("webcam", this);
	}

	BasicModule* create(const nlohmann::json &params)
	{
		int cam_id = 0;
		if (params.find("cam_id") != params.end())
			cam_id = params["cam_id"];
		return new WebCameraFrameProducer(cam_id);
	}
};

static WebCameraFrameProducerFactory global_WebCameraFrameProducerFactory;

