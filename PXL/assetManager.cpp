#include "assetManager.h"

AssetManager::AssetManager()
{
	m_loader = new Loader();
}

RawModel* AssetManager::importMesh(const std::string& filename)
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
		return nullptr;
	}

	const aiMesh* model = scene->mMeshes[0];

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<int> indices;

	const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < model->mNumVertices; i++)
	{
		const aiVector3D pos = model->mVertices[i];
		const aiVector3D normal = model->mNormals[i];
		const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
		const aiVector3D tangent = model->mTangents[i];

		positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
		texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
		normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
	}

	for (unsigned int i = 0; i < model->mNumFaces; i++)
	{
		const aiFace& face = model->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	std::cout << "Loaded new mesh: " << filename << std::endl;

	return &m_loader->loadToVAO(positions, indices, texCoords, normals);
}

AssetManager::~AssetManager()
{
	delete m_loader;
}