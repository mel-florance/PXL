#ifndef _EDITOR_H
#define _EDITOR_H


#include "editorComponent.h"

class Engine;
class Layout;
class Mesh;
class Light;
class EditorLayout;

typedef nlohmann::json typedef1;
class jsontypedef1 {
};
class Editor {
  public:
     Editor(Engine & engine);

    typedef EditorComponent ComponentList;

    typedef EditorComponent ComponentRegister;

    void init();

    void update(double delta);

    static inline EditorComponent registerComponent(Engine & engine);

    inline T createComponent(const std::string & name, const std::string & componentName);

    inline EditorComponent getComponentByName(const std::string & name);

     ~Editor();


  private:
    Engine * m_engine;

    Layout * m_mainLayout;

    Mesh * m_cube;

    Light * m_light;

    class EditorLayout* m_layouts;

    ComponentRegister m_register;

    ComponentList m_components;

    float m_angle;

};
inline EditorComponent Editor::registerComponent(Engine & engine)
{
}

inline T Editor::createComponent(const std::string & name, const std::string & componentName) {
}

inline EditorComponent Editor::getComponentByName(const std::string & name) {
}

#endif
