#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
	unsigned int buffer;

	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	SetRendererID(buffer);
}

VertexBuffer::~VertexBuffer(){
	unsigned int buffer = GetRendererID();

	GLCall(glDeleteBuffers(1, &buffer));
}

void VertexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, GetRendererID()));
}

void VertexBuffer::Unbind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
