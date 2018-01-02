#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "loader.h"


class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	Mesh* importMesh(const std::string& filename);

private:
	Loader* m_loader;
};

