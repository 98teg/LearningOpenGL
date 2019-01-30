#include "TestTexture2D.hpp"

#include "../vendor/imgui/imgui.h"
#include "../VertexBufferLayout.hpp"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"

#include <iostream>

namespace test{
	TestTexture2D::TestTexture2D():	TranslationA(200, 200, 0),
									TranslationB(300, 200, 0),
									ThisShader("Ep22-23-24/res/shaders/basicVertex.shader", "Ep22-23-24/res/shaders/basicFragment.shader"),
									ThisTexture("Ep22-23-24/res/textures/sample.png"){
		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		SetIndexBuffer(new IndexBuffer(indices, 6));

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		float positions[16] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};
		VertexArray* vertex_array = new VertexArray();
		VertexBuffer* vertex_buffer = new VertexBuffer(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		vertex_array->AddBuffer(*vertex_buffer, layout);
		SetVertexArray(vertex_array);
		SetVertexBuffer(vertex_buffer);

		SetProj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f));
		SetView(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

		ThisTexture.Bind();
		GetShader()->Bind();
		GetShader()->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D(){
		delete GetVertexArray();
		delete GetVertexBuffer();
		delete GetIndexBuffer();
	}

	void TestTexture2D::OnRender(){
	    renderer.Clear();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), GetTranslationA());
			glm::mat4 mvp = GetProj() * GetView() * model;
			GetShader()->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*GetVertexArray(), *GetIndexBuffer(), *GetShader());
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), GetTranslationB());
			glm::mat4 mvp = GetProj() * GetView() * model;
			GetShader()->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*GetVertexArray(), *GetIndexBuffer(), *GetShader());
		}

	}

	void TestTexture2D::OnImGuiRender(){
		ImGui::SliderFloat2("Translation A", GetPtrTranslationA(), 0.0f, 640.0f);
		ImGui::SliderFloat2("Translation B", GetPtrTranslationB(), 0.0f, 640.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
