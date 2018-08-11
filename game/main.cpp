#include "StdAfx.h"
#include <cstdio>
#include "util/PathUtil.h"
#include "gles3_render/GLES3RenderStd.h"
#include "gles3_render/GLES3GPUBuffer.h"
#include "gles3_render/GLES3Shader.h"
#include "gles3_render/GLES3RenderEngine.h"

const int WINDOW_SIZE_WIDTH = 800;
const int WINDOW_SIZE_HEIGHT = 600;

int main(int argc, char *argv[])
{
	USING_NAMESPACE_BLADE;
	RenderEngine* renderEngine = BLADE_NEW(RenderEngine);

	WindowSetting setting;
	setting.name = "Blade";
	setting.width = WINDOW_SIZE_WIDTH;
	setting.height = WINDOW_SIZE_HEIGHT;

	if (!renderEngine->initialize(setting))
	{
		return -1;
	}

	// load shaders
	using namespace Blade;
	Buffer buff1, buff2;
	PathUtil::getFileData(buff1, "vertex_shader.txt");
	PathUtil::getFileData(buff2, "fragment_shader.txt");
	std::vector<Blade::Shader*> shaders;
	Shader* shader1 = BLADE_NEW(Shader("vertex_shader.txt", ST_VERTEX_SHADER, buff1));
	Shader* shader2 = BLADE_NEW(Shader("fragment_shader.txt", ST_VERTEX_SHADER, buff2));
	shaders.push_back(shader1);
	shaders.push_back(shader2);
	ShaderProgram* program = BLADE_NEW(ShaderProgram);
	program->setShaders(shaders);
	program->parseParams();
	program->prepareLink();
	program->compileAndLinkShaders();
	shader1->release();
	shader2->release();

	// vertex data
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f, 0.5f, 0.0f  // top   
	};

	VertexElementList vertElms;
	vertElms.resize(1);
	VertexElement &elm0 = vertElms[0];
	elm0.name = "iPosition";
	elm0.format = EF_RGB32_FLOAT;
	elm0.bNormalized = true;

	GPUBufferDesc desc;
	desc.stride = 3 * sizeof(float);
	desc.type = GBT_VERTEX;
	desc.size = sizeof(vertices);
	desc.usage = GBU_STATIC_DRAW;
	desc.buffer = vertices;
	desc.bBak = false;
	GPUBuffer* vbo = BLADE_NEW(GPUBuffer);
	vbo->initialize(desc);

	RenderLayout* layout = BLADE_NEW(RenderLayout);
	layout->initialize(vertElms, program);
	layout->setVertexCount(3);
	layout->setVertexBuffer(0, vbo);
	layout->bindGPUBuffers();

	// render loop
	while (renderEngine->getCurrentRenderWindow()->isActive())
	{
		// input
		renderEngine->getCurrentRenderWindow()->processInput();
		
		renderEngine->clearGLColor(0.2f, 0.3f, 0.3f, 1.0f);
		renderEngine->clear(CM_COLOR);
		renderEngine->render(layout);

		// check call events
		renderEngine->getCurrentRenderWindow()->pollEvents();

		// swap the buffers
		renderEngine->getCurrentRenderWindow()->swapBuffers();
	}

	BLADE_DELETE(program);
	BLADE_DELETE(vbo);

	layout->destroy();
	BLADE_DELETE(layout);

	renderEngine->destroy();
	BLADE_DELETE(renderEngine);

	return 0;
}