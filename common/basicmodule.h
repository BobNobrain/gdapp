#ifndef BASICMODULE_H
#define BASICMODULE_H

#include <QObject>
#include <map>
#include <nlohmann/json.hpp>

class BasicModule;

class ModuleFactory
{
public:
	ModuleFactory() {}

	virtual BasicModule* create(const nlohmann::json& params) = 0;
};

class BasicModule : public QObject
{
	Q_OBJECT
public:
	explicit BasicModule(QObject *parent = 0);

	typedef std::map<std::string, ModuleFactory*> t_map;
	static void registerModule(const std::string& name, ModuleFactory* factory)
	{
		getRegistry()[name] = factory;
	}

	static BasicModule* create(const std::string& name, const nlohmann::json& params)
	{
		auto r = getRegistry();
		auto search = r.find(name);
		if (search == r.end())
			return nullptr;
		return search->second->create(params);
	}

	static t_map& getRegistry()
	{
		static t_map registry = {};
		return registry;
	}
};

#endif // BASICMODULE_H
