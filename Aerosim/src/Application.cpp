#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "FoilMath.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glClearColor(0.2f, 0.4f, 0.8f, 1.0f); // Set background to sky blue

    if (glewInit() != GLEW_OK)
        return -1;
    {
        // Make a bunch of points on an interval for the top and bottom
        // add 640 to x and 360 to y to translate from 0 - 1 to 1280x720
        const int STEP = 10;
        const int NUMVERT = (STEP * 4) + 2;             // Number of vertices * number of coords
        FoilMath fm(4412);                              // TODO: make user input

        GLfloat pos[NUMVERT];

        for (float i = 0.0; i < STEP; ++i) {
            glm::vec2 top = fm.TopFoil(i / STEP);
            glm::vec2 bot = fm.BotFoil(i / STEP);
            pos[((int)i * 2)] = top.x;                  // top vertices will be first half of array
            pos[((int)i * 2) + 1] = top.y;              
            pos[NUMVERT - 2 - ((int)i * 2)] = bot.x;    // bot vertices will be last half of array and reversed
            pos[NUMVERT - 1 - ((int)i * 2)] = bot.y;
        }

        pos[(STEP*4)] = 0.5;
        pos[(STEP*4) + 1] = fm.MeanLine(0.5);

        const int NUMINDS = STEP * 3;
        GLuint indices[NUMINDS];
        int j = 0;

        // Create indices array such that it is STEP (mid of mean line), vert1, vert2
        for (int i = 0; i < STEP; ++i) { 
            indices[j++] = STEP;
            indices[j++] = i;
            indices[j++] = i+1;
        }

        VertexArray va;
		VertexBuffer vb(pos, NUMVERT * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, STEP * 3);

        glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

        Shader shader("res/shaders/basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

            renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
    }
}

    glfwTerminate();
    return 0;
}   