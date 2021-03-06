#include "StdAfx.h"
#include <cstdio>
#include "CoreStd.h"
#include "util/PathUtil.h"
#include "gles3_render/GLES3RenderStd.h"
#include "gles3_render/GLES3GPUBuffer.h"
#include "gles3_render/GLES3Shader.h"
#include "gles3_render/GLES3RenderEngine.h"
#include "gles3_render/GLES3Texture.h"
#include "gles3_render/GLES3RenderStateObject.h"
#include "image/Image.h"
#include "math/Mat4.h"
#include "camera/Camera.h"
#include "light/Light.h"

USING_NAMESPACE_BLADE;
const int WINDOW_SIZE_WIDTH = 1280;
const int WINDOW_SIZE_HEIGHT = 720;

static int64 gStartingTime;
static int64 gFrequency;
static DepthStencilState* gDSS;
static BlendState* gBS;

static void timerInit()
{
	LARGE_INTEGER Frequency;
	LARGE_INTEGER StartingTime;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	gFrequency = Frequency.QuadPart;
	gStartingTime = StartingTime.QuadPart;
}

static inline int64 timerGetMilliseconds()
{
	LARGE_INTEGER now;
	// Query the timer
	QueryPerformanceCounter(&now);

	return ((int64)(now.QuadPart) - gStartingTime) * 1000 / gFrequency;
}

static void initDSS()
{
	DepthStencilStateDesc dssDesc;
	gDSS = BLADE_NEW(DepthStencilState(dssDesc));
}

static void initBS()
{
	BlendStateDesc bsDesc;
	bsDesc.targets[0].bBlend = true;
	bsDesc.targets[0].srcBlend = BF_SRC_ALPHA;
	bsDesc.targets[0].srcAlphaBlend = BF_SRC_ALPHA;
	bsDesc.targets[0].dstBlend = BF_ONE_MINUS_SRC_ALPHA;
	bsDesc.targets[0].dstAlphaBlend = BF_ONE_MINUS_SRC_ALPHA;
	gBS = BLADE_NEW(BlendState(bsDesc));
}

int main(int argc, char *argv[])
{
	timerInit();
	initDSS();
	initBS();

	Camera* gCamera = BLADE_NEW(Camera(CPM_PERSPECTIVE));
	gCamera->setPosition(Vec3(0.0f, 0.0f, 3.0f));
	gCamera->setWidth(WINDOW_SIZE_WIDTH);
	gCamera->setHeight(WINDOW_SIZE_HEIGHT);
	gCamera->setNearAndFarClip(0.1f, 100.0f);

	WindowSetting setting;
	setting.name = "Blade";
	setting.width = WINDOW_SIZE_WIDTH;
	setting.height = WINDOW_SIZE_HEIGHT;
	RenderEngine* renderEngine = BLADE_NEW(RenderEngine);
	if (!renderEngine->initialize(setting))
	{
		return -1;
	}

	renderEngine->setDepthStencilState(gDSS);
	renderEngine->setBlendState(gBS);

	SamplerStateDesc samplerDesc;
	samplerDesc.addrModeU = AM_WRAP;
	samplerDesc.addrModeV = AM_WRAP;
	samplerDesc.minFilter = FO_LINEAR;
	samplerDesc.magFilter = FO_LINEAR;
	samplerDesc.mipFilter = FO_NONE;

	Buffer buff, buffForImage;
	PathUtil::getFileData(buff, "../../resource/marble.jpg");
	ImageFormat imgFmt = Image::getImageFormat("marble.jpg");
	Image *pImage = Image::createFromMemory(buff, imgFmt, false);
	buffForImage.attach(pImage->getSize(), pImage->getData());
	Texture* pTexture = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImage));

	Buffer buffa, buffForImagea;
	PathUtil::getFileData(buffa, "../../resource/metal.png");
	imgFmt = Image::getImageFormat("metal.png");
	pImage = Image::createFromMemory(buffa, imgFmt, false);
	buffForImagea.attach(pImage->getSize(), pImage->getData());
	Texture* pTexture2 = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImagea));

	Buffer buffb, buffForImageb;
	PathUtil::getFileData(buffb, "../../resource/window.png");
	imgFmt = Image::getImageFormat("window.png");
	pImage = Image::createFromMemory(buffb, imgFmt, false);
	buffForImageb.attach(pImage->getSize(), pImage->getData());
	samplerDesc.addrModeU = AM_CLAMP;
	samplerDesc.addrModeV = AM_CLAMP;
	Texture* pTexture3 = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImageb));

	// load shaders
	using namespace Blade;
	Buffer buff1, buff2, buff3;
	PathUtil::getFileData(buff1, "../../resource/blending_testing.vs", true);
	PathUtil::getFileData(buff2, "../../resource/blending_sort_testing.fs", true);

	std::vector<Blade::Shader*> shaders;
	Shader* shader1 = BLADE_NEW(Shader("blending_testing.vs", ST_VERTEX_SHADER, buff1));
	Shader* shader2 = BLADE_NEW(Shader("blending_sort_testing.fs", ST_FRAGMENT_SHADER, buff2));
	shaders.push_back(shader1);
	shaders.push_back(shader2);

	ShaderProgram* program = BLADE_NEW(ShaderProgram);
	program->setShaders(shaders);
	program->prepareLink();
	program->compileAndLinkShaders();
	program->parseParams();
	shader1->release();
	shader2->release();

	// vertex data
	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

	// world space positions of our cubes
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
		5.0f, -0.5f, -5.0f, 2.0f, 2.0f
	};

	float transparentVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.5f, 0.0f, 1.0f, 0.0f
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
	desc.size = sizeof(cubeVertices);
	desc.usage = GBU_STATIC_DRAW;
	desc.buffer = cubeVertices;
	desc.bBak = false;
	GPUBuffer* vbo = BLADE_NEW(GPUBuffer);
	vbo->initialize(desc);

	RenderLayout* cubeLayout = BLADE_NEW(RenderLayout);
	cubeLayout->initialize(vertElms, program);
	cubeLayout->setVertexCount(36);
	cubeLayout->setVertexBuffer(0, vbo);
	cubeLayout->bindGPUBuffers();

	VertexElementList vertElmsForPlane;
	vertElmsForPlane.resize(2);
	VertexElement &elm2 = vertElmsForPlane[0];
	elm2.name = "iPosition";
	elm2.format = EF_RGB32_FLOAT;
	elm2.bNormalized = true;

	VertexElement& elm3 = vertElmsForPlane[1];
	elm3.name = "iTexCoord";
	elm3.format = EF_RG32_FLOAT;
	elm3.bNormalized = true;
	elm3.offset = ELEMENT_SIZE(EF_RGB32_FLOAT);

	desc.stride = 5 * sizeof(float);
	desc.type = GBT_VERTEX;
	desc.size = sizeof(planeVertices);
	desc.usage = GBU_STATIC_DRAW;
	desc.buffer = planeVertices;
	desc.bBak = false;
	GPUBuffer* vbo2 = BLADE_NEW(GPUBuffer);
	vbo2->initialize(desc);

	RenderLayout* planeLayout = BLADE_NEW(RenderLayout);
	planeLayout->initialize(vertElmsForPlane, program);
	planeLayout->setVertexCount(6);
	planeLayout->setVertexBuffer(0, vbo2);
	planeLayout->bindGPUBuffers();

	VertexElementList vertElmsForTransparent;
	vertElmsForTransparent.resize(2);
	VertexElement &elm4 = vertElmsForTransparent[0];
	elm4.name = "iPosition";
	elm4.format = EF_RGB32_FLOAT;
	elm4.bNormalized = true;

	VertexElement& elm5 = vertElmsForTransparent[1];
	elm5.name = "iTexCoord";
	elm5.format = EF_RG32_FLOAT;
	elm5.bNormalized = true;
	elm5.offset = ELEMENT_SIZE(EF_RGB32_FLOAT);

	desc.stride = 5 * sizeof(float);
	desc.type = GBT_VERTEX;
	desc.size = sizeof(transparentVertices);
	desc.usage = GBU_STATIC_DRAW;
	desc.buffer = transparentVertices;
	desc.bBak = false;
	GPUBuffer* vbo3 = BLADE_NEW(GPUBuffer);
	vbo3->initialize(desc);

	RenderLayout* tsLayout = BLADE_NEW(RenderLayout);
	tsLayout->initialize(vertElmsForTransparent, program);
	tsLayout->setVertexCount(6);
	tsLayout->setVertexBuffer(0, vbo3);
	tsLayout->bindGPUBuffers();

	// transparent vegetation locations
	// --------------------------------
	Vec3 vegetation[] = 
	{
		Vec3(-1.5f, 0.0f, -0.48f),
		Vec3(1.5f, 0.0f, 0.51f),
		Vec3(0.0f, 0.0f, 0.7f),
		Vec3(-0.3f, 0.0f, -2.3f),
		Vec3(0.5f, 0.0f, -0.6f)
	};

	std::map<float, Vec3> sorted;

	// render loop
	float deltaTime = 0;
	float lastFrame = (float)(timerGetMilliseconds() * 0.001);
	while (renderEngine->getCurrentRenderWindow()->isActive())
	{
		float currentFrame = (float)(timerGetMilliseconds() * 0.001);
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// check call events
		renderEngine->getCurrentRenderWindow()->pollEvents();

		// input
		renderEngine->getCurrentRenderWindow()->processInput(gCamera, deltaTime);
		gCamera->update();

		for (uint32 i = 0; i < sizeof(vegetation) / sizeof(vegetation[0]); ++i)
		{
			float distance = (gCamera->getPosition() - vegetation[i]).length();
			sorted[distance] = vegetation[i];
		}

		renderEngine->clearGLColor(0.1f, 0.1f, 0.1f, 1.0f);
		renderEngine->clear(CM_COLOR | CM_DEPTH);

		planeLayout->getProgram()->bind();

		Uniform* um;
		um = planeLayout->getProgram()->getUniform("iTex");
		planeLayout->getProgram()->bindTexture(um->getGLLocation(), pTexture2);

		Mat4 vpm = gCamera->getViewProjMatrix();
		um = planeLayout->getProgram()->getUniform("iCamera");
		um->setData(vpm.ptr(), 16 * sizeof(float));

		Mat4 model;
		model.makeTranslate(Vec3(-1.0f, 0.0f, -1.0f));
		um = planeLayout->getProgram()->getUniform("iModel");
		um->setData(model.ptr(), 16 * sizeof(float));

		planeLayout->getProgram()->bindUniforms();
		renderEngine->render(planeLayout);

		cubeLayout->getProgram()->bind();
		um = cubeLayout->getProgram()->getUniform("iTex");
		cubeLayout->getProgram()->bindTexture(um->getGLLocation(), pTexture);
		um = cubeLayout->getProgram()->getUniform("iCamera");
		um->setData(vpm.ptr(), 16 * sizeof(float));
		model.makeTranslate(Vec3(-1.0f, 0.0f, -1.0f));
		um = cubeLayout->getProgram()->getUniform("iModel");
		um->setData(model.ptr(), 16 * sizeof(float));
		cubeLayout->getProgram()->bindUniforms();
		renderEngine->render(cubeLayout);

		model.makeTranslate(Vec3(2.0f, 0.0f, 0.0f));
		um = cubeLayout->getProgram()->getUniform("iModel");
		um->setData(model.ptr(), 16 * sizeof(float));
		cubeLayout->getProgram()->bindUniforms();
		renderEngine->render(cubeLayout);

		tsLayout->getProgram()->bind();
		um = tsLayout->getProgram()->getUniform("iCamera");
		um->setData(vpm.ptr(), 16 * sizeof(float));
		um = tsLayout->getProgram()->getUniform("iTex");
		tsLayout->getProgram()->bindTexture(um->getGLLocation(), pTexture3);
		for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
			model.makeTranslate(it->second);
			um = tsLayout->getProgram()->getUniform("iModel");
			um->setData(model.ptr(), 16 * sizeof(float));
			tsLayout->getProgram()->bindUniforms();
			renderEngine->render(tsLayout);
		}

		// swap the buffers
		renderEngine->getCurrentRenderWindow()->swapBuffers();
	}

	BLADE_DELETE(gDSS);
	BLADE_DELETE(gBS);

	BLADE_DELETE(gCamera);

	BLADE_DELETE(pTexture);
	BLADE_DELETE(pTexture2);

	BLADE_DELETE(program);
	BLADE_DELETE(vbo);
	BLADE_DELETE(vbo2);
	BLADE_DELETE(vbo3);

	cubeLayout->destroy();
	BLADE_DELETE(cubeLayout);

	tsLayout->destroy();
	BLADE_DELETE(tsLayout);

	planeLayout->destroy();
	BLADE_DELETE(planeLayout);

	renderEngine->destroy();
	BLADE_DELETE(renderEngine);

	return 0;
}