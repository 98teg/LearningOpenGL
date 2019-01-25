#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

class VertexArray
{
	private:
		unsigned int RendererID;

		inline unsigned int GetRendererID() const{ return RendererID;};

		inline void SetRendererID(unsigned int rendererID){ RendererID = rendererID;};
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
};

#endif
