#include "Renderer.hpp"

#include <cassert>
#include <iostream>

void GLClearError(){
	while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(){
	bool noError = true;
	GLenum error;

	while(error = glGetError()){
		std::cout << "[OpenGL_Error] (" << error << ")" << std::endl;

		noError = false;
	}

	return noError;
}

void Renderer::Clear() const{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertex_array,
					const IndexBuffer& index_buffer,
					const Shader& shader) const{
	shader.Bind();
	vertex_array.Bind();
	index_buffer.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, index_buffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}
