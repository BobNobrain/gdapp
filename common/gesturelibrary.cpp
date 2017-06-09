#include "gesturelibrary.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GestureLibrary::GestureLibrary() {}
GestureLibrary::~GestureLibrary()
{
	for (AbstractGestureDescriptor* d: contents)
	{
		if (d != nullptr)
			delete d;
	}
}

void GestureLibrary::load(std::string filename)
{
	std::ifstream libContent(filename);
	json data;
	libContent >> data;

	for (json descriptorData: data)
	{
		auto another = AbstractGestureDescriptor::create(descriptorData);
		contents.push_back(another);
	}

	libContent.close();
}

int GestureLibrary::match(AbstractGestureDescriptor *gesture, float accuracy)
{
	int max_id = -1;
	float max_similarity = -1.0F;
	for (AbstractGestureDescriptor* model: contents)
	{
		float how_much = gesture->similarTo(model);
		if (how_much > max_similarity)
		{
			max_id = model->id;
			max_similarity = how_much;
		}
	}
	if (max_similarity >= accuracy)
	{
		// enough similar
		return max_id;
	}
	return -1;
}

std::string& GestureLibrary::getGestureName(int gestureId)
{
	static std::string un = "(unknown name)";
	for (auto d: contents)
	{
		if (d->id == gestureId)
			return d->name;
	}
	return un;
}
