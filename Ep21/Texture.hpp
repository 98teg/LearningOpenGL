#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Renderer.hpp"

class Texture
{
	private:
		unsigned int RendererID;
		int Width, Height, BPP;

		inline unsigned int GetRendererID() const{ return RendererID;};
		inline int GetBPP() const{ return BPP;};

		inline void SetRendererID(unsigned int rendererID){ RendererID = rendererID;};
		inline void SetWidth(int width){ Width = width;};
		inline void SetHeight(int height){ Height = height;};
		inline void SetBPP(int bpp){ BPP = bpp;};
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const{ return Width;};
		inline int GetHeight() const{ return Height;};
};

#endif
