#include "assetManager.h"

struct MaterialInfo
{
	std::string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

AssetManager::AssetManager(Loader* loader, ShaderManager* shaderManager, SceneManager* sceneManager)
{
	m_loader = loader;
	m_shaderManager = shaderManager;
	m_sceneManager = sceneManager;
}

void AssetManager::importMesh(const std::string& filename)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace
	);

	if (!scene) 
		std::cout << importer.GetErrorString() << std::endl;

	this->processNode(scene->mRootNode, scene);
}

void AssetManager::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->processMesh(node->mName, mesh, scene);
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
		this->processNode(node->mChildren[i], scene);
}

Mesh* AssetManager::processMesh(aiString& name, aiMesh* object, const aiScene* scene)
{
	const aiVector3D aiZeroVector(0, 0, 0);
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<int> indices;

	for (GLuint i = 0; i < object->mNumVertices; i++)
	{
		if (object->HasPositions()) {
			const aiVector3D pos = object->mVertices[i];
			vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
		}

		if (object->HasTextureCoords(0)) {
			const aiVector3D texCoord = object->HasTextureCoords(0) ? object->mTextureCoords[0][i] : aiZeroVector;
			uvs.push_back(glm::vec2(texCoord.x, texCoord.y));
		}

		if (object->HasNormals()) {
			const aiVector3D normal = object->mNormals[i];
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		}

		if (object->HasTangentsAndBitangents()) {
			const aiVector3D tangent = object->mTangents[i];
			tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		}
	}

	if (object->HasFaces())
	{
		for (unsigned int i = 0; i < object->mNumFaces; i++)
		{
			const aiFace& face = object->mFaces[i];
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
	}

	Mesh* mesh = m_loader->loadToVAO(name.C_Str(), vertices, indices, uvs, normals, tangents);

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

		std::cout << "Loaded mesh: " << name.C_Str() << std::endl;

		return mesh;
	}
	else 
	{
		std::cout << "Error loading mesh: " << name.C_Str() << std::endl;

		return nullptr;
	}
}

AssetManager::~AssetManager()
{

}