#pragma once

#include <iostream>
#include <algorithm>  

#include "../core/display.h"
#include "../core/engine.h"
#include "../shaders/shader.h"
#include "../mesh/mesh.h"
#include "../cameras/FPSCamera.h"
#include "../materials/basicMaterial.h"
#include "../lighting/light.h"

#include "../ui/core/widget.h"
#include "../ui/widgets/text.h"
#include "../ui/widgets/window.h"
#include "../ui/widgets/image.h"
#include "../ui/widgets/input.h"
#include "../ui/widgets/button.h"
#include "../ui/widgets/label.h"
#include "../ui/widgets/layout.h"


#include "../events/eventListener.h"
#include "../ui/widgets/menu.h"
#include "../ui/widgets/list.h"
#include "../ui/widgets/table.h"
#include "../ui/widgets/icon.h"
#include "../ui/widgets/checkbox.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Game
{ 
public:
	Game(Engine* engine);
	~Game();

	static void callbackFn(CallbackData data);
	static void createCube(CallbackData data);

	void update(double delta);
	AssetManager* m_assetManager;
private:


	Engine* m_engine;
	float m_angle;
	Light* m_light;
	Light* m_lightS;
	Light* m_lightR;
	Text* m_fpsText;
	Scene* m_scene;
	Widget* m_logo;
	FPSCamera* m_camera;
	Mesh* m_dread;

	Text* m_profGame;
	Text* m_profRender;
	Text* m_profInput;
	Text* m_profSwapBuffer;
	Text* m_profSleep;

	Layout* m_layout;

	Label* m_label;
	Input* m_input;

	Button* m_button;

	Label* m_labelName;
	Input* m_inputName;
};
