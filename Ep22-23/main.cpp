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

#include "tests/TestClearColor.hpp"
#include "tests/Test.hpp"

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
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);

		ImGui::StyleColorsDark();

		test::TestMenu menu;
		menu.RegisterTest<test::TestClearColor>("Clear Color");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
		    /* Render here */
			ImGui_ImplGlfwGL3_NewFrame();
			ImGui::Begin("Test");

			if(menu.IsTestSelected()){
				menu.GetCurrent()->OnUpdate(0.0f);
				menu.GetCurrent()->OnRender();

				if(ImGui::Button("<-")){
					menu.DeselecteTest();
					menu.OnImGuiRender();
				}	
				else menu.GetCurrent()->OnImGuiRender();
			}
			else menu.OnImGuiRender();

			ImGui::End();
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
