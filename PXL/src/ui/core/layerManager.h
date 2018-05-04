#ifndef _LAYERMANAGER_H
#define _LAYERMANAGER_H


class Widget;

class LayerManager {
  public:
     LayerManager();

    inline void update(double delta);

    inline std::map<int, std::vector<Widget*>> getLayers();

    inline void addLayer(int id);

    inline bool removeLayer(int layer);

    inline void addWidget(int layer, Widget & widget);

    inline void removeWidget(int layer, Widget & widget);

     ~LayerManager();


  private:
    static const unsigned int MAX_LAYERS;

    int, std::vector<Widget*> m_layers;

};
inline void LayerManager::update(double delta) {
}

inline std::map<int, std::vector<Widget*>> LayerManager::getLayers() {
}

inline void LayerManager::addLayer(int id) {
}

inline bool LayerManager::removeLayer(int layer) {
}

inline void LayerManager::addWidget(int layer, Widget & widget) {
}

inline void LayerManager::removeWidget(int layer, Widget & widget) {
}

#endif
