#include "layerManager.h"

LayerManager::LayerManager()
{
	for(unsigned int i = 0; i < this->MAX_LAYERS; i++)
		this->addLayer(i);
}

LayerManager::~LayerManager()
{

}
