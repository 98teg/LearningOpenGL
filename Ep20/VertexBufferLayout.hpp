#include <vector>
#include <cassert>
#include <GL/glew.h>

#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

struct VertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type){
		switch(type){
			case GL_FLOAT: return sizeof(float);
			case GL_UNSIGNED_INT: return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
		}

		assert(false);
		return 0;
	}
};

namespace VertexBufferLayoutSpecialization
{
	template<typename T>
	unsigned int Type ();

	template<>
	unsigned int Type<float> ();

	template<>
	unsigned int Type<unsigned int>	();

	template<>
	unsigned int Type<unsigned char> ();

	template<typename T>
	unsigned char Normalized ();

	template<>
	unsigned char Normalized<float> ();

	template<>
	unsigned char Normalized<unsigned int>	();

	template<>
	unsigned char Normalized<unsigned char> ();
}

class VertexBufferLayout
{
	private:
		std::vector<VertexBufferLayoutElement> Elements;
		unsigned int Stride;

		inline void AddElement(VertexBufferLayoutElement element){Elements.push_back(element);};

		inline void SetStride(unsigned int stride){Stride = stride;};
	public:
		VertexBufferLayout(){
			SetStride(0);
		};

		template<typename T>
		void Push (unsigned int count) {
			unsigned int type = VertexBufferLayoutSpecialization::Type<T>();

			assert(type != 0);

			unsigned char normalized = VertexBufferLayoutSpecialization::Normalized<T>();

			AddElement({type, count, normalized});
			SetStride(GetStride() + (VertexBufferLayoutElement::GetSizeOfType(type) * count));
		}

		inline const std::vector<VertexBufferLayoutElement>& GetElements() const{return Elements;};
		inline unsigned int GetStride() const{ return Stride;};
};

#endif
