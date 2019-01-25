#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

class VertexBuffer
{
	private:
		unsigned int RendererID;

		inline unsigned int GetRendererID() const{ return RendererID;};

		inline void SetRendererID(unsigned int id){ RendererID = id;};
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
};

#endif
