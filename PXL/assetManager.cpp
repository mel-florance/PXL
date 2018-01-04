#include "assetManager.h"

AssetManager::AssetManager(Loader* loader)
{
	m_loader = loader;
}

Mesh* AssetManager::importMesh(const std::string& filename)
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

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<int> indices;

	const aiVector3D aiZeroVector(0, 0, 0);

	for (unsigned int i = 0; i < model->mNumVertices; i++)
	{
		if (model->HasPositions()) {
			const aiVector3D pos = model->mVertices[i];
			vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
		}
		
		if (model->HasTextureCoords(0)) {
			const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
			uvs.push_back(glm::vec2(texCoord.x, texCoord.y));
		}

		if (model->HasNormals()) {
			const aiVector3D normal = model->mNormals[i];
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		}

		if (model->HasTangentsAndBitangents()) {
			const aiVector3D tangent = model->mTangents[i];
			tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		}
	}

	if (model->HasFaces()) {
		for (unsigned int i = 0; i < model->mNumFaces; i++)
		{
			const aiFace& face = model->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
	}
	
	Mesh* mesh = m_loader->loadToVAO(filename, vertices, indices, uvs, normals, tangents);

	if (mesh != nullptr)
		std::cout << "Loaded mesh: " << filename << std::endl;
	else
		std::cout << "Error loading mesh: " << filename << std::endl;

	return mesh;
}

AssetManager::~AssetManager()
{

}