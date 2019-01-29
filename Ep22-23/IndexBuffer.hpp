#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

class IndexBuffer
{
	private:
		unsigned int RendererID;
		unsigned int Count;

		inline unsigned int GetRendererID() const{ return RendererID;};

		inline void SetRendererID(unsigned int rendererID){ RendererID = rendererID;};
		inline void SetCount(unsigned int count){ Count = count;};
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const{ return Count;};
};

#endif
