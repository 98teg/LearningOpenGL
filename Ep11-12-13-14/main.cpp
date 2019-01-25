#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include "Renderer.hpp"

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
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
		float positions[8] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexArray vertex_array;
		VertexBuffer vertex_buffer(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		vertex_array.AddBuffer(vertex_buffer, layout);

		IndexBuffer index_buffer(indices, 6);

		Shader shader("Ep11-12-13-14/res/shaders/basicVertex.shader", "Ep11-12-13-14/res/shaders/basicFragment.shader");
		shader.Bind();

		float red = 0, green = 0, blue = 0;
		int color = 0;
		bool asc = true;

		vertex_array.Bind();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
		    /* Render here */
		    glClear(GL_COLOR_BUFFER_BIT);

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
	 
			shader.SetUniform4f("u_Color", red, green, blue, 1.0f);
			GLCall(glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, nullptr));

		    /* Swap front and back buffers */
		    glfwSwapBuffers(window);

		    /* Poll for and process events */
		    glfwPollEvents();
		}
	}

    glfwTerminate();
    return 0;
}
