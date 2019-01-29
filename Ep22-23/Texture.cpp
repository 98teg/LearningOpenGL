#include "Texture.hpp"

#include "vendor/stb_image/stb_image.hpp"

#include <iostream>

Texture::Texture(const std::string& path){
	SetRendererID(0);
	SetWidth(0);
	SetHeight(0);
	SetBPP(0);

	stbi_set_flip_vertically_on_load(1);
	int width, height, bpp;
	unsigned char * localbuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	SetWidth(width);
	SetHeight(height);
	SetBPP(bpp);

	unsigned int rendererID;
	GLCall(glGenTextures(1, &rendererID));
	SetRendererID(rendererID);

	GLCall(glBindTexture(GL_TEXTURE_2D, GetRendererID()));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer));

	Unbind();

	if(localbuffer) stbi_image_free(localbuffer);
}

Texture::~Texture(){
	unsigned int rendererID = GetRendererID();
	GLCall(glDeleteTextures(1, &rendererID));
}

void Texture::Bind(unsigned int slot) const{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, GetRendererID()));
}

void Texture::Unbind() const{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
