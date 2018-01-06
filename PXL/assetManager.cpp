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

	if (!scene) {
		std::cout << importer.GetErrorString() << std::endl;
		return;
	}

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
	{
		this->processNode(node->mChildren[i], scene);
	}
}

void AssetManager::processMesh(aiString& name, aiMesh* mesh, const aiScene* scene)
{
	const aiVector3D aiZeroVector(0, 0, 0);
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<int> indices;


	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		if (mesh->HasPositions()) {
			const aiVector3D pos = mesh->mVertices[i];
			vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
		}

		if (mesh->HasTextureCoords(0)) {
			const aiVector3D texCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiZeroVector;
			uvs.push_back(glm::vec2(texCoord.x, texCoord.y));
		}

		if (mesh->HasNormals()) {
			const aiVector3D normal = mesh->mNormals[i];
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		}

		if (mesh->HasTangentsAndBitangents()) {
			const aiVector3D tangent = mesh->mTangents[i];
			tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		}
	}

	if (mesh->HasFaces())
	{
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& face = mesh->mFaces[i];
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
	}

	Mesh* newMesh = m_loader->loadToVAO(name.C_Str(), vertices, indices, uvs, normals, tangents);

	if (newMesh != nullptr)
	{
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

			aiString diffusePath;
			mat->GetTexture(aiTextureType_DIFFUSE, 0, &diffusePath);
			Texture* diffuseTexture = new Texture(diffusePath.C_Str(), true);

			aiString materialName;
			mat->Get(AI_MATKEY_NAME, materialName);

			BasicMaterial* meshMat = new BasicMaterial(materialName.C_Str(), m_shaderManager->getShader("basic"));

			float shininess;
			aiColor3D diffuse;
			aiColor3D ambient;
			aiColor3D specular;

			mat->Get(AI_MATKEY_SHININESS, shininess);
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);

			meshMat->setKa(glm::vec3(ambient.r, ambient.g, ambient.b));
			meshMat->setKd(glm::vec3(diffuse.r, diffuse.g, diffuse.b));
			meshMat->setKs(glm::vec3(specular.r, specular.g, specular.b));

			meshMat->setShininess(shininess);

			if(diffuseTexture != nullptr)
				meshMat->setDiffuseTexture(diffuseTexture);

			newMesh->setMaterial(meshMat);

			m_sceneManager->getCurrentScene()->addMesh(newMesh);
		}

		std::cout << "Loaded mesh: " << name.C_Str() << std::endl;
	}
	else
		std::cout << "Error loading mesh: " << name.C_Str() << std::endl;
}

AssetManager::~AssetManager()
{

}