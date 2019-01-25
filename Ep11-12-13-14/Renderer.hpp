#include <GL/glew.h>
#include <cassert>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLCall(x) GLClearError();\
	x;\
	assert(GLLogCall())

void GLClearError();
bool GLLogCall();

class Renderer{
	public:
		void Clear() const;
		void Draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;
};

#endif
