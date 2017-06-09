#include "stubgda.h"
#include <stdlib.h>
#include <time.h>

StubGDA::StubGDA(std::string glibFilename, float prob): AbstractGDA(glibFilename)
{
	srand (time(NULL));
	generationProbability = prob;
}
StubGDA::~StubGDA() {}

void StubGDA::onNextFrameConsumed(cv::Mat &nextFrame)
{
	float chance = (rand() % 1000) / 1000.F;
	if (chance <= generationProbability)
		onGestureCandidate(nullptr);
}

int StubGDA::classifyGesture(AbstractGestureDescriptor *gesture)
{
	// any gesture here is nullptr and any candidate should be classified as gesture
	return 1;
}

class StubGDAFactory: public ModuleFactory
{
public:
	StubGDAFactory()
	{
		BasicModule::registerModule("stubgda", this);
	}

	BasicModule* create(const nlohmann::json &params)
	{
		StubGDA* result = nullptr;
		auto search = params.find("generation_chance");
		std::string glib_file = params["gesture_library"];
		if (search != params.end())
		{
			double chance = search.value();
			result = new StubGDA(glib_file, (float) chance);
		}
		else
		{
			result = new StubGDA(glib_file);
		}
		return result;
	}
};

static StubGDAFactory global_StubGDAFactory;
