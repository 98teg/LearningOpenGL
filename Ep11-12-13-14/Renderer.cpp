#include "Renderer.hpp"

#include <cassert>
#include <iostream>

void GLClearError(){
	while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(){
	bool noError = true;
	GLenum error;

	while(error = glGetError()){
		std::cout << "[OpenGL_Error] (" << error << ")" << std::endl;

		noError = false;
	}

	return noError;
}
