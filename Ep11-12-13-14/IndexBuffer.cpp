#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count){
	unsigned int buffer;

	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

	SetCount(count);
	SetRendererID(buffer);
}

IndexBuffer::~IndexBuffer(){
	unsigned int buffer = GetRendererID();

	GLCall(glDeleteBuffers(1, &buffer));
}

void IndexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetRendererID()));
}

void IndexBuffer::Unbind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
