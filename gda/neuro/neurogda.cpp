#include "neurogda.h"
#include "image227keyposedescriptor.h"
#include "caffeneuralnet.h"
//#include <QElapsedTimer>

NeuroGDA::NeuroGDA(std::string glibFilename, unsigned int maxPosesPerGesture): KeyPoseGDA(glibFilename, maxPosesPerGesture)
{
	net = nullptr;
}

NeuroGDA::~NeuroGDA()
{
	if (net != nullptr)
		delete net;
}

void NeuroGDA::onNextFrameConsumed(cv::Mat &nextFrame)
{
//	QElapsedTimer timer;
//	timer.start();
	Image227KeyPoseDescriptor i227(nextFrame);
//	std::cerr << "i227: " << timer.elapsed() << std::endl;
	onKeyPoseCandidate(&i227);
}

int NeuroGDA::classifyKeyPose(AbstractPoseDescriptor *pose)
{
	if (net == nullptr) return -1;

	auto i227 = dynamic_cast<Image227KeyPoseDescriptor*> (pose);
	if (i227 == nullptr)
		return -1;

	double prob = 0.0;
//	QElapsedTimer timer;
//	timer.start();
	int poseClass = net->forward(i227->getData(), prob);
//	std::cerr << "net:  " << timer.elapsed() << ", prob " << prob << ", class " << poseClass << std::endl;

	if ((float) prob >= poseMatchingAccuracy)
	{
		return poseClass;
	}
	return -1;
}

class NeuroGDAFactory: public ModuleFactory
{
public:
	NeuroGDAFactory()
	{
		BasicModule::registerModule("neurogda", this);
	}

	BasicModule* create(const nlohmann::json &params)
	{
		std::string bin_file = params["weights"];
		std::string txt_file = params["structure"];
		std::string glib_file = params["gesture_library"];
		int nposes = params["pose_classes_count"];
		unsigned int max_poses = params["max_poses_per_gesture"];
		// TODO: type: caffe/keras/...
		NeuroGDA* result = new NeuroGDA(glib_file, max_poses);
		result->net = new CaffeNeuralNet(bin_file, txt_file, nposes);
		return result;
	}
};

static NeuroGDAFactory global_NeuroGDAFactory;
