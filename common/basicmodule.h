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
		return getRegistry()[name]->create(params);
	}

	static t_map& getRegistry()
	{
		static t_map registry = {};
		return registry;
	}
};

#endif // BASICMODULE_H
