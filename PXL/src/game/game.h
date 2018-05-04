#ifndef _GAME_H
#define _GAME_H


class Engine;
struct CallbackData;
class AssetManager;
class Light;
class Text;
class Scene;
class Widget;
class FPSCamera;
class Mesh;
class Layout;
class Label;
class Input;
class Button;

class Game {
  public:
     Game(Engine & engine);

     ~Game();

    static void callbackFn(const CallbackData & data);

    static void createCube(const CallbackData & data);

    static void newProject(const CallbackData & data);

    static void setFullscreen(const CallbackData & data);

    static void exitApplication(const CallbackData & data);

    void update(double delta);

    AssetManager * m_assetManager;


  private:
    Engine * m_engine;

    float m_angle;

    Light * m_light;

    Light * m_lightS;

    Light * m_lightR;

    Text * m_fpsText;

    Scene * m_scene;

    Widget * m_logo;

    FPSCamera * m_camera;

    Mesh * m_dread;

    Text * m_profGame;

    Text * m_profRender;

    Text * m_profInput;

    Text * m_profSwapBuffer;

    Text * m_profSleep;

    Layout * m_layout;

    Label * m_label;

    Input * m_input;

    Button * m_button;

    Label * m_labelName;

    Input * m_inputName;

};
#endif
