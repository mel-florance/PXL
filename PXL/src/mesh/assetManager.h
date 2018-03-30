#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../core/loader.h"
#include "../texturing/texture.h"
#include "../materials/basicMaterial.h"
#include "../shaders/shaderManager.h"
#include "../scene/sceneManager.h"

class AssetManager
{
public:
	AssetManager(Loader* loader, ShaderManager* shaderManager, SceneManager* sceneManager);
	~AssetManager();

	void importMesh(const std::string& filename);
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiString& name, aiMesh* mesh, const aiScene* scene); // TODO: should return a Mesh*

	inline Loader* getLoader() { return m_loader; }

private:
	Loader* m_loader;
	ShaderManager* m_shaderManager;
	SceneManager* m_sceneManager;
};

