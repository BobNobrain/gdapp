#include "pipebuilder.h"

PipeBuilder::PipeBuilder() {}
PipeBuilder::~PipeBuilder()
{
	reinit();
}

void PipeBuilder::reinit()
{
	for (BasicModule* module: created)
	{
		if (module != nullptr)
			delete module;
	}
	created.clear();
}

AbstractFrameProducer* PipeBuilder::build(const json& config)
{
	std::string module = config["module"];
	json params = config["params"];
	json consumers = config["consumers"];

	std::cout << "Initializing root module: " << module << std::endl;

	BasicModule* root = BasicModule::create(module, params);
	created.push_back(root);
	AbstractFrameProducer* fp = dynamic_cast<AbstractFrameProducer*> (root);

	if (fp == nullptr)
	{
		std::cerr << "Error: root module should be a frame producer!" << std::endl;
		exit(1);
	}
	else
	{
		buildGDAs(consumers, fp);
	}
	return fp;
}

void PipeBuilder::buildGDAs(const json &consumers, AbstractFrameProducer *parent)
{
	for (json c: consumers)
	{
		std::string module = c["module"];

		std::cout << "Initializing second-line module: " << module << std::endl;

		json params = json::object();
		if (c.find("params") != c.end())
		{
			params = c["params"];
		}

		BasicModule* node = BasicModule::create(module, params);
		created.push_back(node);
		AbstractFrameConsumer* as_consumer = dynamic_cast<AbstractFrameConsumer*> (node);
		if (as_consumer == nullptr)
		{
			std::cerr << "Error: second-line module should be a frame consumer!" << std::endl;
			exit(1);
		}
		else
		{
			as_consumer->consume(parent);

			json consumers = json::array();
			if (c.find("consumers") != c.end())
			{
				consumers = c["consumers"];
			}

			if (consumers.size() > 0)
			{
				// hmm, that means that we deal with GDA
				auto as_gda = dynamic_cast<AbstractGDA*> (node);
				if (as_gda == nullptr)
				{
					std::cerr << "Error: second-line module that have consumers should be a GDA!" << std::endl;
					exit(1);
				}
				else
				{
					buildListeners(consumers, as_gda);
				}
			}
		}
	}
}

void PipeBuilder::buildListeners(const json &consumers, AbstractGDA *parent)
{
	for (json c: consumers)
	{
		std::string module = c["module"];

		std::cout << "Initializing third-line module: " << module << std::endl;

		json params = json::object();
		if (c.find("params") != c.end())
		{
			params = c["params"];
		}

		if (c.find("consumers") != c.end())
		{
			std::cerr << "Warning: consumers list detected for third-line module! List ignored" << std::endl;
		}

		auto node = BasicModule::create(module, params);
		created.push_back(node);
		AbstractGestureListener* gl = dynamic_cast<AbstractGestureListener*> (node);
		if (gl == nullptr)
		{
			std::cerr << "Error: third-line module should be a gesture listener!" << std::endl;
			exit(1);
		}
		gl->listen(parent->getDetector());
	}
}
