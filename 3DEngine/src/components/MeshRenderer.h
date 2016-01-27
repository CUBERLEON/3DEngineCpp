#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Component.h"

class Mesh;
class Material;
class Shader;
class RenderingEngine;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh* mesh, Material* material);
	~MeshRenderer();
protected:
private:
	Mesh* m_mesh;
	Material* m_material;

	void render(Shader* shader, RenderingEngine* renderingEngine) override;
};

#endif // MESH_RENDERER_H
