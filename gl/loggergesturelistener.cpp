#include "loggergesturelistener.h"
#include <fstream>

LoggerGestureListener::LoggerGestureListener(std::ostream* os)
{
	outs = os;
}
LoggerGestureListener::~LoggerGestureListener() {}

void LoggerGestureListener::onGestureDetected(int gestureId)
{
	(*outs) << "Gesture detected! id=" << gestureId << ", name=" << detector->getGestureName(gestureId) << std::endl;
}

class FileLoggerGestureListener: public LoggerGestureListener
{
public:
	FileLoggerGestureListener(std::ostream* os): LoggerGestureListener(os) {}
	~FileLoggerGestureListener()
	{
		std::ofstream* ofs = dynamic_cast<std::ofstream*> (outs);
		if (ofs != nullptr)
		{
			ofs->close();
			delete ofs;
		}
	}
};

class LoggerGestureListenerFactory: public ModuleFactory
{
public:
	LoggerGestureListenerFactory()
	{
		BasicModule::registerModule("logger", this);
	}

	BasicModule* create(const nlohmann::json &params)
	{
		std::string type = params["type"];
		std::string ost = params["ostream"];

		if (type == "file")
		{
			std::ofstream* file = new std::ofstream(ost);
			FileLoggerGestureListener* fl = new FileLoggerGestureListener(file);
			return fl;
		}
		if (type == "stream")
		{
			std::ostream* o = nullptr;
			if (ost == "cout") o = &std::cout;
			if (ost == "cerr") o = &std::cerr;
			if (o == nullptr)
			{
				std::cerr << "Error! Logger cannot use specified stream '" << ost << "', only 'cout' and 'cerr' are supported!" << std::endl;
				exit(1);
			}
			LoggerGestureListener* l = new LoggerGestureListener(o);
			return l;
		}

		std::cerr << "Error! Logger of given type '" << type << "' is not supported!" << std::endl;
		exit(1);
	}
};

static LoggerGestureListenerFactory global_LoggerGestureListenerFactory;
