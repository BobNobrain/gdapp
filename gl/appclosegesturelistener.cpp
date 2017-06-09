#include "appclosegesturelistener.h"

AppCloseGestureListener::AppCloseGestureListener(int gestId, bool twice)
{
	gest = gestId;
	repeat = twice;
	done_once = false;
}
AppCloseGestureListener::~AppCloseGestureListener() {}

void AppCloseGestureListener::onGestureDetected(int gestureId)
{
	if (gestureId == gest)
	{
		if (done_once || !repeat)
		{
			std::cout << "AppCloseGestureListener: closing application!" << std::endl;
			exit(0);
		}
		else
		{
			done_once = true;
			std::cout << "Repeat this gesture to close the application" << std::endl;
		}
	}
	else
	{
		done_once = false;
	}
}

class AppCloseGLFactory: public ModuleFactory
{
public:
	AppCloseGLFactory()
	{
		BasicModule::registerModule("appclose", this);
	}

	BasicModule* create(const nlohmann::json &params)
	{
		int gid = params["gesture_id"];
		bool twice = true;
		auto search = params.find("repeat_twice");
		if (search != params.end())
		{
			twice = search.value();
		}
		AppCloseGestureListener* result = new AppCloseGestureListener(gid, twice);
		return result;
	}
};

static AppCloseGLFactory global_AppCloseGLFactory;
