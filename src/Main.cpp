#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Reference 1 : https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.1.hello_triangle/hello_triangle.cpp
// Referenec 2 : http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left  
     0.5f, -0.5f, 0.0f, // right 
     0.0f,  0.5f, 0.0f  // top   
};

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Fix compilation on OS X
#endif
}

GLFWwindow* createWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn : CMake and Conan", nullptr, nullptr);

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

void draw(GLFWwindow* window, unsigned int shaderProgram, unsigned int vao)
{
	glClearColor(0.529f, 0.808f, 0.922f, 0.0f);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

unsigned int createVertexShader()
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Error : vertex shader compilation failed" << std::endl << infoLog << std::endl;
    }

    return vertexShader;
}

unsigned int createFragmentShader()
{
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Error : fragment shader compilation failed" << std::endl << infoLog << std::endl;
    }

    return fragmentShader;
}

unsigned int createShaderProgram()
{
    unsigned int vertexShader = createVertexShader();
    unsigned int fragmentShader = createFragmentShader();


    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Error : shader linkage failed" << std::endl << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void fillVboWithTriangle(unsigned int vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
}

void cleanup(unsigned int vao, unsigned int vbo)
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
}

int main()
{
	initGlfw();
	setWindowHints();
	GLFWwindow* window = createWindow();
	glfwMakeContextCurrent(window);
	initGlew();

	// Ensure we can capture the escape key being pressed below (TODO : change for polling)
	glfwSetInputMode(window, GLFW_STICKY_KEYS, true);

    unsigned int shaderProgram = createShaderProgram();


    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    fillVboWithTriangle(vbo);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	draw(window, shaderProgram, vao);

    cleanup(vao, vbo);

	return EXIT_SUCCESS;
}