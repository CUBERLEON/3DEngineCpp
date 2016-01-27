#include "MeshRenderer.h"

#include "../rendering/Mesh.h"
#include "../rendering/Material.h"
#include "../rendering/RenderingEngine.h"
#include "../rendering/shaders/Shader.h"
#include "../core/Transform.h"
#include "../core/Debug.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material)
{
	m_mesh = mesh;
	m_material = material;
}

MeshRenderer::~MeshRenderer()
{
	m_material = nullptr;
	delete m_mesh;
	delete m_material;
}

void MeshRenderer::render(Shader* shader, RenderingEngine* renderingEngine)
{
	shader->bind();
	shader->updateUniforms(getTransform(), m_material, renderingEngine);
	m_mesh->draw();
}
