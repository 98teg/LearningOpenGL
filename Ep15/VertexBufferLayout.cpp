#include "VertexBufferLayout.hpp"

template<typename T>
unsigned int VertexBufferLayoutSpecialization::Type () {
	return 0;
}

template<>
unsigned int VertexBufferLayoutSpecialization::Type<float> () {
	return GL_FLOAT;
}

template<>
unsigned int VertexBufferLayoutSpecialization::Type<unsigned int>	() {
	return GL_UNSIGNED_INT;
}

template<>
unsigned int VertexBufferLayoutSpecialization::Type<unsigned char> () {
	return GL_UNSIGNED_BYTE;
}

template<typename T>
unsigned char VertexBufferLayoutSpecialization::Normalized () {
	return 0;
}

template<>
unsigned char VertexBufferLayoutSpecialization::Normalized<float> () {
	return GL_FALSE;
}

template<>
unsigned char VertexBufferLayoutSpecialization::Normalized<unsigned int>	() {
	return GL_FALSE;
}

template<>
unsigned char VertexBufferLayoutSpecialization::Normalized<unsigned char> () {
	return GL_TRUE;
}
