#include "Renderer.h"

void Renderer::Draw(const Entity& entity, const Shader& shader) const {
	entity.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, entity.GetIBOSize() / 3, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
