#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

bool initGlfw()
{
	glewExperimental = true;
	bool isGlfwInitialized = glfwInit();

	if (!isGlfwInitialized)
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return isGlfwInitialized;
}

void setWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
}

GLFWwindow* createWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST : conan_learn", nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	return window;
}

bool initGlew()
{
	bool glewErrorCode = glewInit();

	if (glewErrorCode != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	return glewErrorCode;
}

void draw(GLFWwindow* window)
{
	glClearColor(0.529f, 0.808f, 0.922f, 0.0f);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	std::cout << "TEST : conan_learn" << std::endl;
	
	initGlfw();
	setWindowHints();
	GLFWwindow* window = createWindow();
	glfwMakeContextCurrent(window);
	initGlew();

	// Ensure we can capture the escape key being pressed below (TODO : change for polling)
	glfwSetInputMode(window, GLFW_STICKY_KEYS, true);

	draw(window);

	glfwTerminate();

	return EXIT_SUCCESS;
}