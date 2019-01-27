#include <string>
#include <unordered_map>

#include "vendor/glm/glm.hpp"

#ifndef SHADER_HPP
#define SHADER_HPP

class Shader
{
	private:
		unsigned int RendererID;
		std::unordered_map<std::string, int> UniformLocationCache;

		inline unsigned int GetRendererID() const{ return RendererID;};
		int GetUniformLocation(const std::string& name);

		inline void SetRendererID(unsigned int rendererID){ RendererID = rendererID;};

		std::string ReadShader(const std::string& filepath);
		unsigned int CompileShader(	unsigned int type,
									const std::string &source);
		unsigned int CreateShader(	const std::string& vertexShader,
									const std::string& fragmentShader);
		inline bool UniformLocationCacheHas(const std::string& name){
			return UniformLocationCache.find(name) != UniformLocationCache.end();
		};

		inline int UniformLocationCacheGet(const std::string& name){
			return UniformLocationCache[name];
		};

		inline void UniformLocationCacheAdd(const std::string& name, int location){
			UniformLocationCache[name] = location;
		};
	public:
		Shader(const std::string& filepath_vertex, const std::string& filepath_fragment);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Set uniform
		void SetUniform1i(const std::string& name, int v);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};

#endif
