#pragma once

#include <iostream>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "FPSCamera.h"
#include "basicMaterial.h"
#include "text.h"
#include "light.h"
#include "engine.h"
#include "widget.h"
#include "window.h"
#include "image.h"
#include "input.h"
#include "label.h"

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

