#pragma once

#include "entityComponent.h"
#include "mesh/mesh.h"

class MeshRenderer : public EntityComponent
{
public:
	MeshRenderer(const Mesh& mesh, const Material& material) :
		m_mesh(mesh),
		m_material(material) {}

	~MeshRenderer() {}

private:
	Mesh m_mesh;
	Material m_material;
};

