#ifndef _EDITORCOMPONENT_H
#define _EDITORCOMPONENT_H


class Engine;
class Layout;

class EditorComponent {
  public:
     EditorComponent(Engine & engine);

    virtual  ~EditorComponent();

    inline virtual void init();

    inline virtual void update(double delta);

    void setLayout(Layout & layout);

    Layout getLayout();

    void setEngine(Engine & engine);

    Engine getEngine();


  private:
    Layout * m_layout;

    Engine * m_engine;

};
inline void EditorComponent::init() {
}

inline void EditorComponent::update(double delta) {
}

#endif
