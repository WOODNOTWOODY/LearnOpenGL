#include "GLES3RenderStd.h"
#include "GLES3RenderWindow.h"
#include "GLES3RenderEngine.h"

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
	BLADE_SAFE_DELETE(m_pContext);
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
	m_pContext = BLADE_NEW(RenderContext(this));

	ContextOption op;
	m_pContext->initialize(op);

	m_pContext->bind();

	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return false;
	}

	glViewport(0, 0, m_width, m_height);

	DepthStencilState* pDefaultDSS = RenderEngine::Instance()->getDefaultDepthStencilState();
	pDefaultDSS->bind(true);
	m_pContext->setDepthStencilState(pDefaultDSS);

	return true;
}

void RenderWindow::destroy()
{
	m_pContext->destroy();
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

void RenderWindow::processInput(Camera* camera, float deltaTime)
{
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_glfwWindow, true);
	}

	if (glfwGetKey(m_glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		Vec3 offset = Vec3(0, 0, -1);
		offset *= (2.5 * deltaTime);
		camera->move(offset);
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		Vec3 offset = Vec3(0, 0, 1);
		offset *= (2.5 * deltaTime);
		camera->move(offset);
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		Vec3 offset = -camera->getRight();
		offset *= (2.5 * deltaTime);
		camera->move(offset);
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		Vec3 offset = camera->getRight();
		offset *= (2.5 * deltaTime);
		camera->move(offset);
	}
}

void RenderWindow::pollEvents()
{
	glfwPollEvents();
}

BLADE_NAMESPACE_END