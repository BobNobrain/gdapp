#include <QCoreApplication>
#include <nlohmann/json.hpp>
#include <fstream>
#include "common/pipebuilder.h"
#include "common/abstractframeproducer.h"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	std::ifstream config_stream("config.json");
	if (!config_stream.good())
	{
		std::cerr << "No config.json file found!" << std::endl;
		exit(2);
	}
	json config_json;
	config_stream >> config_json;

	std::cout << "Start building pipeline..." << std::endl;

	PipeBuilder builder;
	AbstractFrameProducer* root = builder.build(config_json);
	if (root != nullptr)
	{
		root->startProducing();
	}

	return a.exec();
}
