#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include "Renderer.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"

int main(void){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	GLenum err = glewInit();
	if (GLEW_OK != err){
	  /* Problem: glewInit failed, something is seriously wrong. */
	  std::cerr << "Error: " << glewGetErrorString(err);
	}

	{
		float positions[16] = {
			100.0f, 100.0f, 0.0f, 0.0f,
			200.0f, 100.0f, 1.0f, 0.0f,
			200.0f, 200.0f, 1.0f, 1.0f,
			100.0f, 200.0f, 0.0f, 1.0f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray vertex_array;
		VertexBuffer vertex_buffer(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		vertex_array.AddBuffer(vertex_buffer, layout);

		IndexBuffer index_buffer(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

		Shader shader("Ep17-18-19/res/shaders/basicVertex.shader", "Ep17-18-19/res/shaders/basicFragment.shader");

		Texture texture("Ep17-18-19/res/textures/sample.png");
		texture.Bind();
		shader.Bind();
		shader.SetUniform1i("u_Texture", 0);

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);

		ImGui::StyleColorsDark();

		glm::vec3 translation(200, 200, 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
		    /* Render here */
		    renderer.Clear();

			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);

			ImGui_ImplGlfwGL3_NewFrame();

			renderer.Draw(vertex_array, index_buffer, shader);

		    {
		        ImGui::SliderFloat2("float", &translation.x, 0.0f, 640.0f);
		        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		    }

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		    /* Swap front and back buffers */
		    glfwSwapBuffers(window);

		    /* Poll for and process events */
		    glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
