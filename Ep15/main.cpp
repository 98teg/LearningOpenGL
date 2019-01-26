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
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
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

		Shader shader("Ep15/res/shaders/basicVertex.shader", "Ep15/res/shaders/basicFragment.shader");

		Texture texture("Ep15/res/textures/sample.png");
		texture.Bind();
		shader.Bind();
		shader.SetUniform1i("u_Texture", 0);

		float red = 0, green = 0, blue = 0;
		int color = 0;
		bool asc = true;

		Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
		    /* Render here */
		    renderer.Clear();

			if(asc){
				if(color == 0 && red >= 1){
					color = 1;
					green = green + 0.1f;
				}
				else if(color == 0) red = red + 0.1f;
				else if(color == 1 && green >= 1){
					color = 2;
					blue = blue + 0.1f;
				}
				else if(color == 1) green = green + 0.1f;
				else if(color == 2 && blue >= 1){
					color = 0;
					red = red - 0.1f;
					asc = false;
				}
				else blue = blue + 0.1f;
			}
			else{
				if(color == 0 && red <= 0){
					color = 1;
					green = green - 0.1f;
				}
				else if(color == 0) red = red - 0.1f;
				else if(color == 1 && green <= 0){
					color = 2;
					blue = blue - 0.1f;
				}
				else if(color == 1) green = green - 0.1f;
				else if(color == 2 && blue <= 0){
					color = 0;
					red = red + 0.1f;
					asc = true;
				}
				else blue = blue - 0.1f;
			}


			shader.Bind();
			shader.SetUniform4f("u_Color", red, green, blue, 1.0f);
			renderer.Draw(vertex_array, index_buffer, shader);

		    /* Swap front and back buffers */
		    glfwSwapBuffers(window);

		    /* Poll for and process events */
		    glfwPollEvents();
		}
	}

    glfwTerminate();
    return 0;
}
