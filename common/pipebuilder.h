#ifndef PIPEBUILDER_H
#define PIPEBUILDER_H

#include <nlohmann/json.hpp>
#include <vector>
#include "basicmodule.h"
#include "abstractframeproducer.h"
#include "abstractframeconsumer.h"
#include "abstractgesturelistener.h"
#include "gda/abstractgda.h"

using json = nlohmann::json;

class PipeBuilder
{
public:
	PipeBuilder();

	AbstractFrameProducer* build(const json& config);

	~PipeBuilder();
private:
	std::vector<BasicModule*> created;

	void reinit();
	void buildGDAs(const json& consumers, AbstractFrameProducer* parent);
	void buildListeners(const json& consumers, AbstractGDA* parent);
};

#endif // PIPEBUILDER_H
