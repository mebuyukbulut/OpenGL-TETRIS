#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
	Display(int width, int height, std::string title);
	~Display();

	void Update();

	bool should_window_close();

	GLFWwindow* get_window();

private:
	GLFWwindow* window;
	// settings
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;
};

