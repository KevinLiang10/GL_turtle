#define GLFW_INCLUDE_NONE
#include "turtle.h"
#include <math.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
								   "uniform vec4 ourColor;"
								   "out vec4 FragColor;\n"
								   "void main()\n"
								   "{\n"
								   "   FragColor = ourColor;\n"
								   "}\n\0";

Turtle::Turtle(){};
Turtle::~Turtle() { glfwTerminate(); };

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Turtle::init(float x, float y, float theta)
{
	v.x = x;
	v.y = y;
	v.z = 0;

	this->theta = theta;
}

void Turtle::show()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, 0.0f, 0.0f);

		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, turtleColor.x, turtleColor.y, turtleColor.z, 1.0f);

		glDrawArrays(GL_LINES, 0, vertices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Turtle::forward(float d)
{
	float ds = d * STEP; 

	vertices.push_back(v);

	v.x += ds * sin(theta);
	v.y += ds * cos(theta);

	vertices.push_back(v);
}

void Turtle::right(float theta)
{
	//Implement this function
	this->theta += (theta * M_PI / 180);
}

void Turtle::left(float theta)
{
	//Implement his function
	this->theta -= (theta * M_PI / 180);
}

void Turtle::setPosition(float x, float y)
{

	v.x = x;
	v.y = y;

}

void Turtle::circle(float radius)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 100; i++)
	{
		glVertex2f(
			v.x + (radius * STEP * cos(i * 2.0f * M_PI / 100)),
			v.y + (radius * STEP * sin(i * 2.0f * M_PI / 100)));
	}
	glEnd();
}

void Turtle::penup()
{
	//Implement this function
	down = false;
}

void Turtle::pendown()
{
	//Implement this function
	down = true;
}

void Turtle::color(float r, float g, float b)
{
	turtleColor.x = r;
	turtleColor.y = g;
	turtleColor.z = b;
}