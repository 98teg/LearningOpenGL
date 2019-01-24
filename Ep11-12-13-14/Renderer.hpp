#include <GL/glew.h>
#include <cassert>

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLCall(x) GLClearError();\
	x;\
	assert(GLLogCall())

void GLClearError();
bool GLLogCall();

#endif
