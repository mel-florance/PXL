
#include "layerManager.h"
#include "widget.h"

 LayerManager::LayerManager() {

	for(unsigned int i = 0; i < this->MAX_LAYERS; i++)
		this->addLayer(i);
}

 LayerManager::~LayerManager() {


}

const unsigned int LayerManager::MAX_LAYERS=  32;

