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

class Game
{
public:
	Game(Engine* engine);
	~Game();

	glm::vec2 setGuiScale(const glm::vec2& scale);
	void update(double delta);

private:
	Engine* m_engine;
	Mesh* m_ak;
	float m_angle;
	Light* m_light;
	Light* m_lightS;
	Light* m_lightR;
	Text* m_fpsText;
	Scene* m_scene;
	Widget* m_logo;

	Text* m_profGame;
	Text* m_profRender;
	Text* m_profInput;
	Text* m_profSwapBuffer;
	Text* m_profSleep;
};

