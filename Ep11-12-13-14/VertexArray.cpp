#include "VertexArray.hpp"

VertexArray::VertexArray(){
	unsigned int vertex_array;
	GLCall(glGenVertexArrays(1, &vertex_array));

	SetRendererID(vertex_array);
}

VertexArray::~VertexArray(){
	unsigned int vertex_array = GetRendererID();

	GLCall(glDeleteVertexArrays(1, &vertex_array));
}

void VertexArray::Bind() const{
	GLCall(glBindVertexArray(GetRendererID()));
}

void VertexArray::Unbind() const{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& layout){
	Bind();

	vertex_buffer.Bind();

	const std::vector<VertexBufferLayoutElement>& elements = layout.GetElements();

	int * offset = 0;

	for(int i = 0; i < elements.size(); i++){
		VertexBufferLayoutElement element = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *) offset));

		offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
	}
}
