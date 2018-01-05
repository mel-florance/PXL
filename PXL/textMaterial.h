#pragma once

#include "texture.h"
#include "material.h"

class TextMaterial : public Material
{
public:
	TextMaterial(const std::string& name, Shader* shader);
	~TextMaterial();

	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }
	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }

	virtual void preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights);
	virtual void postUpdate();

	virtual void bindAttributes();

private:
	Texture* m_diffuseTexture;
};

