#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		return -1;
	}

	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	// Create a vertex buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Fill the vertex buffer with data
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle
		// 1. Bind the vertex buffer
		// 2. Tell OpenGL what the layout of the vertex buffer is
		// 3. Draw the triangle
		// 4. Unbind the vertex buffer
		// 5. Swap front and back buffers
		// 6. Poll for and process events
		// 7. Terminate the program
		
		// Bind the vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		// Tell OpenGL what the layout of the vertex buffer is
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Unbind the vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
