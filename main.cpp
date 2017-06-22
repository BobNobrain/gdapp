#include <QCoreApplication>
#include <nlohmann/json.hpp>
#include <fstream>
#include "common/pipebuilder.h"
#include "common/abstractframeproducer.h"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	std::string config_file_name = "config.json";

	if (argc > 1)
	{
		config_file_name = argv[1];
	}

	std::ifstream config_stream(config_file_name);
	if (!config_stream.good())
	{
		std::cerr << (argc > 1? "Bad config file specified!" : "No config.json file found!") << std::endl;
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
