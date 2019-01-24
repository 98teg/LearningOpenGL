#ifndef IndexBuffer_HPP
#define IndexBuffer_HPP

class IndexBuffer
{
	private:
		unsigned int RendererID;
		unsigned int Count;

		inline unsigned int getRendererID() const{ return RendererID;};

		inline void setRendererID(unsigned int rendererID){ RendererID = rendererID;};
		inline void setCount(unsigned int count){ Count = count;};
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int getCount() const{ return Count;};
};

#endif
