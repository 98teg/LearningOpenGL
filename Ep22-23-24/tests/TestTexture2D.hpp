#include "Test.hpp"

#include "../Texture.hpp"

#ifndef TESTTEXTURE2D_HPP
#define TESTTEXTURE2D_HPP

namespace test{

	class TestTexture2D: public Test{
		private:
			glm::vec3 TranslationA;
			glm::vec3 TranslationB;
			glm::mat4 Proj;
			glm::mat4 View;
			Shader ThisShader;
			VertexArray* Vertex_array;
			VertexBuffer* Vertex_buffer;
			IndexBuffer* Index_buffer;
			Texture ThisTexture;
			Renderer renderer;

			inline glm::vec3 GetTranslationA() const{return TranslationA;};
			inline glm::vec3 GetTranslationB() const{return TranslationB;};

			inline float* GetPtrTranslationA() {return &(TranslationA.x);};
			inline float* GetPtrTranslationB() {return &(TranslationB.x);};

			inline Shader* GetShader() {return &ThisShader;};
			inline VertexArray* GetVertexArray() {return Vertex_array;};
			inline VertexBuffer* GetVertexBuffer() {return Vertex_buffer;};
			inline IndexBuffer* GetIndexBuffer() {return Index_buffer;};

			inline glm::mat4 GetProj() const{return Proj;};
			inline glm::mat4 GetView() const{return View;};

			inline void SetTranslationA(const glm::vec3& trans) {TranslationA = trans;};
			inline void SetTranslationB(const glm::vec3& trans) {TranslationB = trans;};

			inline void SetProj(const glm::mat4& proj) {Proj = proj;};
			inline void SetView(const glm::mat4& view) {View = view;};

			inline void SetVertexArray(VertexArray* vertex_array) {Vertex_array = vertex_array;};
			inline void SetVertexBuffer(VertexBuffer* vertex_buffer) {Vertex_buffer = vertex_buffer;};
			inline void SetIndexBuffer(IndexBuffer* index_buffer) {Index_buffer = index_buffer;};
		public:
			TestTexture2D();
			~TestTexture2D();

			void OnRender() override;
			void OnImGuiRender() override;
	};

}

#endif
