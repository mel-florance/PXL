#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <string>

#include <nlohmann/json.hpp>

#include "../core/engine.h"
#include "../cameras/FPSCamera.h"

#include "components/mainMenu.h"
#include "components/viewport.h"
#include "components/outliner.h"
#include "components/assetBrowser.h"

using json = nlohmann::json;

class Editor
{
public:
	Editor();

	typedef std::map<std::string, EditorComponent*> ComponentList;
	typedef std::map<std::string, EditorComponent*(*)(Engine*)> ComponentRegister;
	
	void init();
	void update(double delta);

	template<typename T>
	static EditorComponent* registerComponent(Engine* engine) { return new T(engine); }

	template<typename T>
	T* createComponent(const std::string& name, const std::string& componentName) 
	{
		T* component = (T*)m_register[componentName](m_engine);
		m_components[name] = component;
		return component;
	}

	inline EditorComponent* getComponentByName(const std::string& name)
	{
		ComponentList::iterator it;
		for (it = m_components.begin(); it != m_components.end(); it++)
			if(it->first == name)
				return it->second;

		return nullptr;
	}

	~Editor();

private:
	Engine* m_engine;
	Layout* m_mainLayout;
	Mesh* m_cube;
	Light* m_light;

	std::vector<class EditorLayout*> m_layouts;
	ComponentRegister m_register;
	ComponentList m_components;
	float m_angle;

};
