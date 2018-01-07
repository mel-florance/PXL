#pragma once

#include <iostream>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "pointLight.h"
#include "basicMaterial.h"
#include "text.h"
#include "pointLight.h"
#include "engine.h"

class Game
{
public:
	Game(Engine* engine);
	~Game();

	void update(double delta);

private:
	Engine* m_engine;
	Mesh* m_ak;
	float m_angle;
	Text* m_fpsText;
	Scene* m_scene;
};

