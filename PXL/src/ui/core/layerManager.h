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
		//m_layers.erase(std::remove(m_layers.begin(), m_layers.end(), layer), m_layers.end());
	}

	inline void addWidget(int layer, Widget* widget)
	{
		m_layers[layer].push_back(widget);
	}

	inline void removeWidget(int layer, Widget* widget)
	{
		//m_layers[layer].erase(std::remove(m_layers[layer].begin(), m_layers[layer].end(), widget), m_layers[layer].end());
	}

	~LayerManager();

private:
	std::map<int, std::vector<Widget*>> m_layers;
};

