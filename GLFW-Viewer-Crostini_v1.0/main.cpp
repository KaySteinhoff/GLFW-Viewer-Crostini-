#include <iostream>
#include "shader.h"
#include "linmath.h"

typedef struct
{
	float x, y;
	float r, g, b;
}vert;

vert verts[6] = {
	{0.0, 0.0, 0.0, 0.0, 0.0},
	{1.0, 0.0, 1.0, 0.0, 0.0},
	{1.0, 1.0, 1.0, 1.0, 0.0},

	{0.0, 1.0, 0.0, 1.0, 0.0},
	{1.0, 1.0, 1.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0}
};


int main(int argc, char** argv)
{
	GLFWwindow* win;

	if(!glfwInit())
		return -1;
	win = glfwCreateWindow(500, 500, "Test window", NULL, NULL);
	if(!win)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(win);

	GLenum err = glewInit();

	GLuint shader, VBO;
	std::cout << "Creating VBO..." << std::endl;
	glGenBuffers(1, &VBO);
	std::cout << "Binding VBO..." << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	std::cout << "Creating shader..." << std::endl;
	shader = CreateShader("shader.frag", "shader.vert");

	GLint aPos = glGetAttribLocation(shader, "aPos");
	GLint vCol = glGetAttribLocation(shader, "vCol");
	GLint _MVP = glGetUniformLocation(shader, "MVP");
	glEnableVertexAttribArray(aPos);
	glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, sizeof(verts[0]), (void*) 0);
	glEnableVertexAttribArray(vCol);
	glVertexAttribPointer(vCol, 3, GL_FLOAT, GL_FALSE, sizeof(verts[0]), (void*) (sizeof(float) * 2));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	float ratio = 500/500;
	mat4x4 m, p, mvp;

	while(!glfwWindowShouldClose(win))
	{
		glViewport(0, 0, 500, 500);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_perspective(p, 90, ratio, 0.01f, 100.0f);
		mat4x4_mul(mvp, p, m);

		glUseProgram(shader);
		glUniformMatrix4fv(_MVP, 1, GL_FALSE, (const GLfloat*) mvp);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(verts) / sizeof(verts[0]));

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwTerminate();

	return 0;
}
