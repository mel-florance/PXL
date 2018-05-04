#pragma once

#include <map>
#include <algorithm>

#include "widget.h"

class LayerManager
{
public:
	LayerManager();

	inline void update(double delta) { }

	inline std::map<int, std::vector<Widget*>>& getLayers() { return m_layers; }

	inline void addLayer(int id)
	{ 
		m_layers[id] = std::vector<Widget*>();
	}

	bool removeLayer(int layer)
	{
		std::map<int, std::vector<Widget*>>::iterator it = m_layers.find(layer);

		if (it != m_layers.end())
		{
			m_layers.erase(it);
			return true;
		}

		return false;
	}

	inline void addWidget(int layer, Widget* widget)
	{
		std::map<int, std::vector<Widget*>>::iterator it = m_layers.find(layer);

		if (it != m_layers.end())
			if (std::find(it->second.begin(), it->second.end(), widget) == it->second.end())
				it->second.emplace_back(widget);
	}

	inline void removeWidget(int layer, Widget* widget)
	{
		std::map<int, std::vector<Widget*>>::iterator it = m_layers.find(layer);

		if (it != m_layers.end())
			if (std::find(it->second.begin(), it->second.end(), widget) != it->second.end())
				it->second.erase(std::remove(it->second.begin(), it->second.end(), widget), it->second.end());
	}

	~LayerManager();

private:
	static const unsigned int MAX_LAYERS = 32;
	std::map<int, std::vector<Widget*>> m_layers;
};

