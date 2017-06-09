#ifndef ABSTRACTGESTUREDESCRIPTOR_H
#define ABSTRACTGESTUREDESCRIPTOR_H

#include <nlohmann/json.hpp>
#include <map>
using json = nlohmann::json;

class AbstractGestureDescriptor;

class GestureDescriptorFactory
{
public:
	virtual AbstractGestureDescriptor* create(const json& params) = 0;
};

class AbstractGestureDescriptor
{
public:
	AbstractGestureDescriptor();
	~AbstractGestureDescriptor();

	virtual float similarTo(AbstractGestureDescriptor* templateDesctiptor) = 0;

	std::string name;
	int id;

	static void registerType(std::string name, GestureDescriptorFactory* factory)
	{
		getRegistry()[name] = factory;
	}

	static AbstractGestureDescriptor* create(const json& data)
	{
		auto r = getRegistry();
		std::string type = data["type"];
		auto search = r.find(type);
		if (search == r.end())
		{
			std::cerr << "Warning: cannot find gesture descriptor of type '" << type << "'! This can crash the program!" << std::endl;
			return nullptr;
		}
		auto result = search->second->create(data);
		result->id = data["id"];
		if (data.find("name") != data.end())
		{
			result->name = data["name"];
		}
		return result;
	}

private:
	typedef std::map<std::string, GestureDescriptorFactory*> registry_t;
	static registry_t& getRegistry()
	{
		static registry_t registry;
		return registry;
	}
};

#endif // ABSTRACTGESTUREDESCRIPTOR_H
