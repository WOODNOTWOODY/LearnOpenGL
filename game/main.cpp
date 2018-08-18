#include "StdAfx.h"
#include <cstdio>
#include "util/PathUtil.h"
#include "gles3_render/GLES3RenderStd.h"
#include "gles3_render/GLES3GPUBuffer.h"
#include "gles3_render/GLES3Shader.h"
#include "gles3_render/GLES3RenderEngine.h"
#include "gles3_render/GLES3Texture.h"
#include "gles3_render/GLES3RenderStateObject.h"
#include "image/Image.h"
#include "math/Mat4.h"

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

	SamplerStateDesc samplerDesc;
	samplerDesc.addrModeU = AM_WRAP;
	samplerDesc.addrModeV = AM_WRAP;
	samplerDesc.minFilter = FO_LINEAR;
	samplerDesc.magFilter = FO_LINEAR;
	samplerDesc.mipFilter = FO_NONE;

	Buffer buff, buffForImage;
	PathUtil::getFileData(buff, "../../resource/container.jpg");
	ImageFormat imgFmt = Image::getImageFormat("container.jpg");
	Image *pImage = Image::createFromMemory(buff, imgFmt, false);
	buffForImage.attach(pImage->getSize(), pImage->getData());
	Texture* pTexture = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImage));

	Buffer buffa, buffForImagea;
	PathUtil::getFileData(buffa, "../../resource/awesome_face.png");
	imgFmt = Image::getImageFormat("awesome_face.png");
	pImage = Image::createFromMemory(buffa, imgFmt, false);
	buffForImagea.attach(pImage->getSize(), pImage->getData());
	Texture* pTexture2 = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImagea));

	// load shaders
	using namespace Blade;
	Buffer buff1, buff2;
	PathUtil::getFileData(buff1, "../../resource/vertex_shader.txt", true);
	PathUtil::getFileData(buff2, "../../resource/fragment_shader.txt", true);
	std::vector<Blade::Shader*> shaders;
	Shader* shader1 = BLADE_NEW(Shader("vertex_shader.txt", ST_VERTEX_SHADER, buff1));
	Shader* shader2 = BLADE_NEW(Shader("fragment_shader.txt", ST_FRAGMENT_SHADER, buff2));
	shaders.push_back(shader1);
	shaders.push_back(shader2);
	ShaderProgram* program = BLADE_NEW(ShaderProgram);
	program->setShaders(shaders);
	program->prepareLink();
	program->compileAndLinkShaders();
	program->parseParams();
	shader1->release();
	shader2->release();

	Uniform* uf = program->getUniform("iTex");
	program->bindTexture(uf->getGLLocation(), pTexture);

	uf = program->getUniform("iTex2");
	program->bindTexture(uf->getGLLocation(), pTexture2);

	// vertex data
	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,// right 
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // left  
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f  // top   
	};

	uint32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	VertexElementList vertElms;
	vertElms.resize(2);
	VertexElement &elm0 = vertElms[0];
	elm0.name = "iPosition";
	elm0.format = EF_RGB32_FLOAT;
	elm0.bNormalized = true;

	VertexElement& elm1 = vertElms[1];
	elm1.name = "iTexCoord";
	elm1.format = EF_RG32_FLOAT;
	elm1.bNormalized = true;
	elm1.offset = ELEMENT_SIZE(EF_RGB32_FLOAT);

	GPUBufferDesc desc;
	desc.stride = 5 * sizeof(float);
	desc.type = GBT_VERTEX;
	desc.size = sizeof(vertices);
	desc.usage = GBU_STATIC_DRAW;
	desc.buffer = vertices;
	desc.bBak = false;
	GPUBuffer* vbo = BLADE_NEW(GPUBuffer);
	vbo->initialize(desc);

	GPUBufferDesc desc2;
	desc2.type = GBT_INDEX;
	desc2.stride = sizeof(uint32);
	desc2.size = sizeof(indices);
	desc2.buffer = indices;
	desc2.bBak = false;
	GPUBuffer* ebo = BLADE_NEW(GPUBuffer);
	ebo->initialize(desc2);

	RenderLayout* layout = BLADE_NEW(RenderLayout);
	layout->initialize(vertElms, program);
	layout->setVertexCount(3);
	layout->setVertexBuffer(0, vbo);
	layout->setIndexBuffer(ebo);
	layout->bindGPUBuffers();

	float identity[16] =
	{ 1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };
	Mat4 test(identity);
	printf("IsIdentify:%d\n", test.isIdentify());

	// render loop
	while (renderEngine->getCurrentRenderWindow()->isActive())
	{
		// check call events
		renderEngine->getCurrentRenderWindow()->pollEvents();

		// input
		renderEngine->getCurrentRenderWindow()->processInput();
		
		renderEngine->clearGLColor(0.2f, 0.3f, 0.3f, 1.0f);
		renderEngine->clear(CM_COLOR);

		layout->getProgram()->bind();
		layout->getProgram()->bindUniforms();
		renderEngine->render(layout);

		// swap the buffers
		renderEngine->getCurrentRenderWindow()->swapBuffers();
	}

	BLADE_DELETE(pTexture);

	BLADE_DELETE(program);
	BLADE_DELETE(vbo);

	layout->destroy();
	BLADE_DELETE(layout);

	renderEngine->destroy();
	BLADE_DELETE(renderEngine);

	return 0;
}