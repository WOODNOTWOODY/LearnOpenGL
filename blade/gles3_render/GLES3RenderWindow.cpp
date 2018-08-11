#include "GLES3RenderStd.h"
#include "GLES3RenderWindow.h"

BLADE_NAMESPACE_BEGIN

RenderWindow::RenderWindow()
	: m_name("")
	, m_left(0)
	, m_top(0)
	, m_width(800)
	, m_height(600)
{

}

RenderWindow::~RenderWindow()
{

}

bool RenderWindow::initialize(const WindowSetting& setting)
{
	m_name = setting.name;
	m_left = setting.left;
	m_top = setting.top;
	m_width = setting.width;
	m_height = setting.height;

	// initialize glfw
	glfwInit();

	// opwn a window with glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
	if (!m_glfwWindow)
	{
		printf("Failed to create GLFW window\n");
		return false;
	}

	// glfw settings
	glfwMakeContextCurrent(m_glfwWindow);

	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return false;
	}

	glViewport(0, 0, m_width, m_height);

	return true;
}

void RenderWindow::destroy()
{
	glfwMakeContextCurrent(NULL);
	glfwTerminate();
}

void RenderWindow::swapBuffers()
{
	glfwSwapBuffers(m_glfwWindow);
}

bool RenderWindow::isActive()
{
	return !glfwWindowShouldClose(m_glfwWindow);
}

void RenderWindow::processInput()
{
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_glfwWindow, true);
	}
}

void RenderWindow::pollEvents()
{
	glfwPollEvents();
}

BLADE_NAMESPACE_END