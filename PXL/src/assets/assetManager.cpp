
#include "assetManager.h"
#include "loader.h"
#include "shadermanager.h"
#include "sceneManager.h"
#include "mesh.h"
#include "texture.h"

 AssetManager::AssetManager(Loader & loader, ShaderManager & shaderManager, SceneManager & sceneManager) {

	m_loader = loader;
	m_shaderManager = shaderManager;
	m_sceneManager = sceneManager;
}

 AssetManager::~AssetManager() {


}

void AssetManager::importMesh(const std::string & filename) {

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename,
		//aiProcess_GenSmoothNormals |
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace
	);

	if (!scene) 
	{
		std::cout << importer.GetErrorString() << std::endl;
		return;
	}

	this->processNode(scene->mRootNode, scene);
}

void AssetManager::processNode(aiNode & node, const aiScene & scene) {

	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->processMesh(node->mName.C_Str(), mesh, scene);
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
		this->processNode(node->mChildren[i], scene);
}

Mesh AssetManager::processMesh(const std::string & name, aiMesh & object, const aiScene & scene) {

	std::vector<GLuint> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;

	for (GLuint i = 0; i < object->mNumVertices; i++)
	{
		if (object->HasPositions())
			vertices.push_back(glm::vec3(object->mVertices[i].x, object->mVertices[i].y, object->mVertices[i].z));

		if (object->HasTextureCoords(0)) 
			uvs.push_back(glm::vec2(object->mTextureCoords[0][i].x, object->mTextureCoords[0][i].y));

		if (object->HasNormals())
			normals.push_back(glm::vec3(object->mNormals[i].x, object->mNormals[i].y, object->mNormals[i].z));

		if (object->HasTangentsAndBitangents())
			tangents.push_back(glm::vec3(object->mTangents[i].x, object->mTangents[i].y, object->mTangents[i].z));
	}

	if (object->HasFaces())
	{
		for (unsigned int i = 0; i < object->mNumFaces; i++)
		{
			indices.push_back((GLuint)object->mFaces[i].mIndices[0]);
			indices.push_back((GLuint)object->mFaces[i].mIndices[1]);
			indices.push_back((GLuint)object->mFaces[i].mIndices[2]);
		}
	}

	if (uvs.size() == 0) 
	{
		std::cout << "Object \"" << name << "\" has no uv coordinates, import cancelled.";
		return nullptr;
	}

	Mesh* mesh = m_loader->loadToVAO(name, vertices, indices, uvs, normals, tangents);

	if (mesh != nullptr)
	{
		Scene* currentScene = m_sceneManager->getCurrentScene();
		currentScene->addMesh(mesh);

		if (object->mMaterialIndex >= 0)
		{
			aiMaterial* mat = scene->mMaterials[object->mMaterialIndex];

			aiString materialName;
			mat->Get(AI_MATKEY_NAME, materialName);

			BasicMaterial* material = new BasicMaterial(materialName.C_Str(), m_shaderManager->getShader("basic"));
			currentScene->addMaterial(material);

			aiString diffusePath;
			mat->GetTexture(aiTextureType_DIFFUSE, 0, &diffusePath);

			if (strlen(diffusePath.C_Str()) > 0) 
			{
				Texture* diffuseTexture = new Texture(diffusePath.C_Str(), true);
				material->setDiffuseTexture(diffuseTexture);
			}

			aiString specularPath;
			mat->GetTexture(aiTextureType_SHININESS, 0, &specularPath);

			if (strlen(specularPath.C_Str()) > 0)
			{
				Texture* specularTexture = new Texture(specularPath.C_Str(), true);
				material->setSpecularTexture(specularTexture);
			}

			aiString normalPath;
			mat->GetTexture(aiTextureType_HEIGHT, 0, &normalPath);
			
			if (strlen(normalPath.C_Str()) > 0)
			{
				Texture* normalTexture = new Texture(normalPath.C_Str(), true);
				material->setNormalTexture(normalTexture);
			}

			aiColor3D diffuse;
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			material->setKd(glm::vec3(diffuse.r, diffuse.g, diffuse.b));

			aiColor3D ambient;
			mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			material->setKa(glm::vec3(ambient.r, ambient.g, ambient.b));

			float shininess = 10.0f;
			mat->Get(AI_MATKEY_SHININESS, shininess);
			material->setShininess(shininess);

			aiColor3D specular;
			mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			material->setKs(glm::vec3(specular.r, specular.g, specular.b));

			float exponent = 1.0f;
			mat->Get(AI_MATKEY_SHININESS_STRENGTH, exponent);
			material->setExponent(exponent);

			float alpha = 1.0f;
			mat->Get(AI_MATKEY_OPACITY, alpha);
			material->setAlpha(alpha);

			float reflectivity = 0.0f;
			mat->Get(AI_MATKEY_REFLECTIVITY, reflectivity);
			material->setReflectivity(reflectivity);

			mesh->setMaterial(material);
		}

		std::cout << "Loaded mesh: " << name << std::endl;

		return mesh;
	}
	else 
	{
		std::cout << "Error loading mesh: " << name << std::endl;

		return nullptr;
	}
}

