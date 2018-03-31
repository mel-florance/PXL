#pragma once

#include <iostream>

#include "core/display.h"
#include "shaders/shader.h"
#include "mesh/mesh.h"
#include "texturing/texture.h"
#include "cameras/FPSCamera.h"
#include "materials/basicMaterial.h"
#include "lighting/light.h"
#include "core/engine.h"
#include "ui/text.h"
#include "ui/widget.h"
#include "ui/window.h"
#include "ui/image.h"
#include "ui/input.h"
#include "ui/label.h"

class Game
{ 
public:
	Game(Engine* engine);
	~Game();

	void update(double delta);

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

	Input* m_input;
	Label* m_label;
};

