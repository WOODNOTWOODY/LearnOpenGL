#include "StdAfx.h"
//#include <cstdio>
//#include "CoreStd.h"
//#include "util/PathUtil.h"
//#include "gles3_render/GLES3RenderStd.h"
//#include "gles3_render/GLES3GPUBuffer.h"
//#include "gles3_render/GLES3Shader.h"
//#include "gles3_render/GLES3RenderEngine.h"
//#include "gles3_render/GLES3Texture.h"
//#include "gles3_render/GLES3RenderStateObject.h"
//#include "image/Image.h"
//#include "math/Mat4.h"
//#include "camera/Camera.h"
//#include "light/Light.h"
//
//USING_NAMESPACE_BLADE;
//const int WINDOW_SIZE_WIDTH = 800;
//const int WINDOW_SIZE_HEIGHT = 600;
//
//static int64 gStartingTime;
//static int64 gFrequency;
//
//DirectionalLight gDirLight;
//PointLight gPointLights[4];
//SpotLight gSpotLight;
//
//static void timerInit()
//{
//	LARGE_INTEGER Frequency;
//	LARGE_INTEGER StartingTime;
//
//	QueryPerformanceFrequency(&Frequency);
//	QueryPerformanceCounter(&StartingTime);
//
//	gFrequency = Frequency.QuadPart;
//	gStartingTime = StartingTime.QuadPart;
//}
//
//static inline int64 timerGetMilliseconds()
//{
//	LARGE_INTEGER now;
//	// Query the timer
//	QueryPerformanceCounter(&now);
//
//	return ((int64)(now.QuadPart) - gStartingTime) * 1000 / gFrequency;
//}
//
//static inline void lightInit(Camera* camera)
//{
//	// directional light
//	gDirLight.setDirection(Vec3(-0.2f, -1.0f, -0.3f));
//	gDirLight.setColor(PC_AMBIENT, Color(0.05f, 0.05f, 0.05f));
//	gDirLight.setColor(PC_DIFFUSE, Color(0.4f, 0.4f, 0.4f));
//	gDirLight.setColor(PC_SPECULAR, Color(0.5f, 0.5f, 0.5f));
//
//	// point light 1
//	gPointLights[0].setPosition(Vec3(0.7f, 0.2f, 2.0f));
//	gPointLights[0].setColor(PC_AMBIENT, Color(0.05f, 0.05f, 0.05f));
//	gPointLights[0].setColor(PC_DIFFUSE, Color(0.8f, 0.8f, 0.8f));
//	gPointLights[0].setColor(PC_SPECULAR, Color(1.0f, 1.0f, 1.0f));
//	gPointLights[0].setAttenuation(50.0f, 1.0f, 0.09f, 0.032f);
//
//	// point light 2
//	gPointLights[1].setPosition(Vec3(2.3f, -3.3f, -4.0f));
//	gPointLights[1].setColor(PC_AMBIENT, Color(0.05f, 0.05f, 0.05f));
//	gPointLights[1].setColor(PC_DIFFUSE, Color(0.8f, 0.8f, 0.8f));
//	gPointLights[1].setColor(PC_SPECULAR, Color(1.0f, 1.0f, 1.0f));
//	gPointLights[1].setAttenuation(50.0f, 1.0f, 0.09f, 0.032f);
//
//	// point light 3
//	gPointLights[2].setPosition(Vec3(-4.0f, 2.0f, -12.0f));
//	gPointLights[2].setColor(PC_AMBIENT, Color(0.05f, 0.05f, 0.05f));
//	gPointLights[2].setColor(PC_DIFFUSE, Color(0.8f, 0.8f, 0.8f));
//	gPointLights[2].setColor(PC_SPECULAR, Color(1.0f, 1.0f, 1.0f));
//	gPointLights[2].setAttenuation(50.0f, 1.0f, 0.09f, 0.032f);
//
//	// point light 4
//	gPointLights[3].setPosition(Vec3(0.0f, 0.0f, -3.0f));
//	gPointLights[3].setColor(PC_AMBIENT, Color(0.05f, 0.05f, 0.05f));
//	gPointLights[3].setColor(PC_DIFFUSE, Color(0.8f, 0.8f, 0.8f));
//	gPointLights[3].setColor(PC_SPECULAR, Color(1.0f, 1.0f, 1.0f));
//	gPointLights[3].setAttenuation(50.0f, 1.0f, 0.09f, 0.032f);
//
//	// spot light
//	gSpotLight.setPosition(camera->getPosition());
//	gSpotLight.setDirection(-camera->getDirection());
//	gSpotLight.setColor(PC_AMBIENT, Color(0.0f, 0.0f, 0.0f));
//	gSpotLight.setColor(PC_DIFFUSE, Color(1.0f, 1.0f, 1.0f));
//	gSpotLight.setColor(PC_SPECULAR, Color(1.0f, 1.0f, 1.0f));
//	gSpotLight.setAttenuation(50.0f, 1.0f, 0.09f, 0.032f);
//	gSpotLight.setSpotInner(std::cos(12.5 * Math::PI / 180));
//	gSpotLight.setSpotInner(std::cos(15.0 * Math::PI / 180));
//}
//
//int main(int argc, char *argv[])
//{
//	timerInit();
//
//	Camera* gCamera = BLADE_NEW(Camera(CPM_PERSPECTIVE));
//	gCamera->setPosition(Vec3(0.0f, 0.0f, 3.0f));
//	gCamera->setWidth(WINDOW_SIZE_WIDTH);
//	gCamera->setHeight(WINDOW_SIZE_HEIGHT);
//	gCamera->setNearAndFarClip(0.1f, 100.0f);
//
//	lightInit(gCamera);
//
//	WindowSetting setting;
//	setting.name = "Blade";
//	setting.width = WINDOW_SIZE_WIDTH;
//	setting.height = WINDOW_SIZE_HEIGHT;
//	RenderEngine* renderEngine = BLADE_NEW(RenderEngine);
//	if (!renderEngine->initialize(setting))
//	{
//		return -1;
//	}
//
//	SamplerStateDesc samplerDesc;
//	samplerDesc.addrModeU = AM_WRAP;
//	samplerDesc.addrModeV = AM_WRAP;
//	samplerDesc.minFilter = FO_LINEAR;
//	samplerDesc.magFilter = FO_LINEAR;
//	samplerDesc.mipFilter = FO_NONE;
//
//	Buffer buff, buffForImage;
//	PathUtil::getFileData(buff, "../../resource/container2.png");
//	ImageFormat imgFmt = Image::getImageFormat("container2.png");
//	Image *pImage = Image::createFromMemory(buff, imgFmt, false);
//	buffForImage.attach(pImage->getSize(), pImage->getData());
//	Texture* pTexture = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
//		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImage));
//
//	Buffer buffa, buffForImagea;
//	PathUtil::getFileData(buffa, "../../resource/container2_specular.png");
//	imgFmt = Image::getImageFormat("container2_specular.png");
//	pImage = Image::createFromMemory(buffa, imgFmt, false);
//	buffForImagea.attach(pImage->getSize(), pImage->getData());
//	Texture* pTexture2 = BLADE_NEW(Texture(TT_2D, pImage->getElementFormat(), 0, pImage->getWidth(),
//		pImage->getHeight(), pImage->getDepth(), 1, samplerDesc, buffForImagea));
//
//	// load shaders
//	using namespace Blade;
//	Buffer buff1, buff2, buff3, buff4;
//	PathUtil::getFileData(buff1, "../../resource/light.vs", true);
//	PathUtil::getFileData(buff2, "../../resource/light.fs", true);
//	PathUtil::getFileData(buff3, "../../resource/lamp.vs", true);
//	PathUtil::getFileData(buff4, "../../resource/lamp.fs", true);
//
//	std::vector<Blade::Shader*> shaders;
//	Shader* shader1 = BLADE_NEW(Shader("light.vs", ST_VERTEX_SHADER, buff1));
//	Shader* shader2 = BLADE_NEW(Shader("light.fs", ST_FRAGMENT_SHADER, buff2));
//	shaders.push_back(shader1);
//	shaders.push_back(shader2);
//
//	ShaderProgram* lightingProgram = BLADE_NEW(ShaderProgram);
//	lightingProgram->setShaders(shaders);
//	lightingProgram->prepareLink();
//	lightingProgram->compileAndLinkShaders();
//	lightingProgram->parseParams();
//	shader1->release();
//	shader2->release();
//
//	shaders.clear();
//	Shader* shader3 = BLADE_NEW(Shader("lamp.vs", ST_VERTEX_SHADER, buff3));
//	Shader* shader4 = BLADE_NEW(Shader("lamp.fs", ST_FRAGMENT_SHADER, buff4));
//	shaders.push_back(shader3);
//	shaders.push_back(shader4);
//
//	ShaderProgram* lampProgram = BLADE_NEW(ShaderProgram);
//	lampProgram->setShaders(shaders);
//	lampProgram->prepareLink();
//	lampProgram->compileAndLinkShaders();
//	lampProgram->parseParams();
//	shader3->release();
//	shader4->release();
//
//	Uniform* uf = lightingProgram->getUniform("material.diffuse");
//	lightingProgram->bindTexture(uf->getGLLocation(), pTexture);
//
//	uf = lightingProgram->getUniform("material.specular");
//	lightingProgram->bindTexture(uf->getGLLocation(), pTexture2);
//
//	// vertex data
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//
//		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//
//		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//
//		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
//		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
//
//		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
//	};
//
//	// world space positions of our cubes
//	Vec3 cubePositions[] = {
//		Vec3(0.0f, 0.0f, 0.0f),
//		Vec3(2.0f, 5.0f, -15.0f),
//		Vec3(-1.5f, -2.2f, -2.5f),
//		Vec3(-3.8f, -2.0f, -12.3f),
//		Vec3(2.4f, -0.4f, -3.5f),
//		Vec3(-1.7f, 3.0f, -7.5f),
//		Vec3(1.3f, -2.0f, -2.5f),
//		Vec3(1.5f, 2.0f, -2.5f),
//		Vec3(1.5f, 0.2f, -1.5f),
//		Vec3(-1.3f, 1.0f, -1.5f)
//	};
//
//	VertexElementList vertElms;
//	vertElms.resize(3);
//	VertexElement &elm0 = vertElms[0];
//	elm0.name = "iPosition";
//	elm0.format = EF_RGB32_FLOAT;
//	elm0.bNormalized = true;
//
//	VertexElement& elm1 = vertElms[1];
//	elm1.name = "iNormal";
//	elm1.format = EF_RGB32_FLOAT;
//	elm1.bNormalized = true;
//	elm1.offset = ELEMENT_SIZE(EF_RGB32_FLOAT);
//
//	VertexElement& elm2 = vertElms[2];
//	elm2.name = "iTexCoord";
//	elm2.format = EF_RG32_FLOAT;
//	elm2.bNormalized = true;
//	elm2.offset = 2 * ELEMENT_SIZE(EF_RGB32_FLOAT);
//
//	GPUBufferDesc desc;
//	desc.stride = 8 * sizeof(float);
//	desc.type = GBT_VERTEX;
//	desc.size = sizeof(vertices);
//	desc.usage = GBU_STATIC_DRAW;
//	desc.buffer = vertices;
//	desc.bBak = false;
//	GPUBuffer* vbo = BLADE_NEW(GPUBuffer);
//	vbo->initialize(desc);
//
//	RenderLayout* lightingLayout = BLADE_NEW(RenderLayout);
//	lightingLayout->initialize(vertElms, lightingProgram);
//	lightingLayout->setVertexCount(36);
//	lightingLayout->setVertexBuffer(0, vbo);
//	lightingLayout->bindGPUBuffers();
//
//	vertElms.resize(1);
//	VertexElement &elm4 = vertElms[0];
//	elm4.name = "iPosition";
//	elm4.format = EF_RGB32_FLOAT;
//	elm4.bNormalized = true;
//
//	RenderLayout* lampLayout = BLADE_NEW(RenderLayout);
//	lampLayout->initialize(vertElms, lampProgram);
//	lampLayout->setVertexCount(36);
//	lampLayout->setVertexBuffer(0, vbo);
//	lampLayout->bindGPUBuffers();
//
//	// render loop
//	float deltaTime = 0;
//	float lastFrame = (float)(timerGetMilliseconds() * 0.001);
//	while (renderEngine->getCurrentRenderWindow()->isActive())
//	{
//		float currentFrame = (float)(timerGetMilliseconds() * 0.001);
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// check call events
//		renderEngine->getCurrentRenderWindow()->pollEvents();
//
//		// input
//		renderEngine->getCurrentRenderWindow()->processInput(gCamera, deltaTime);
//		gCamera->update();
//
//		gSpotLight.setPosition(gCamera->getPosition());
//		gSpotLight.setDirection(-gCamera->getDirection());
//		
//		renderEngine->clearGLColor(0.2f, 0.3f, 0.3f, 1.0f);
//		renderEngine->clear(CM_COLOR | CM_DEPTH);
//
//		lightingLayout->getProgram()->bind();
//
//		Uniform* um;
//		Mat4 vpm = gCamera->getViewProjMatrix();
//		um = lightingLayout->getProgram()->getUniform("iCamera");
//		um->setData(vpm.ptr(), 16 * sizeof(float));
//
//		Vec3 pos = gCamera->getPosition();
//		um = lightingLayout->getProgram()->getUniform("cameraPos");
//		um->setData(pos.m, 3 * sizeof(float));
//
//		um = lightingLayout->getProgram()->getUniform("material.shininess");
//		um->setValue(32.0f);
//
//		um = lightingLayout->getProgram()->getUniform("dirLight.direction");
//		um->setData((void*)gDirLight.getDirection().m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("dirLight.ambient");
//		um->setData((void*)gDirLight.getColor(PC_AMBIENT).m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("dirLight.diffuse");
//		um->setData((void*)gDirLight.getColor(PC_DIFFUSE).m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("dirLight.specular");
//		um->setData((void*)gDirLight.getColor(PC_SPECULAR).m, 3 * sizeof(float));
//
//		char buff[16];
//		for (int i = 0; i < 4; ++i)
//		{
//			sprintf(buff, "pointLights[%d].", i);
//			std::string name = buff;
//			um = lightingLayout->getProgram()->getUniform(name + "position");
//			um->setData((void*)gPointLights[i].getPosition().m, 3 * sizeof(float));
//			um = lightingLayout->getProgram()->getUniform(name + "ambient");
//			um->setData((void*)gPointLights[i].getColor(PC_AMBIENT).m, 3 * sizeof(float));
//			um = lightingLayout->getProgram()->getUniform(name + "diffuse");
//			um->setData((void*)gPointLights[i].getColor(PC_DIFFUSE).m, 3 * sizeof(float));
//			um = lightingLayout->getProgram()->getUniform(name + "specular");
//			um->setData((void*)gPointLights[i].getColor(PC_SPECULAR).m, 3 * sizeof(float));
//			um = lightingLayout->getProgram()->getUniform(name + "constant");
//			um->setValue(gPointLights[i].getAttenuationConstant());
//			um = lightingLayout->getProgram()->getUniform(name + "linear");
//			um->setValue(gPointLights[i].getAttenuationLinear());
//			um = lightingLayout->getProgram()->getUniform(name + "quadratic");
//			um->setValue(gPointLights[i].getAttenuationQuadratic());
//		}
//		
//		um = lightingLayout->getProgram()->getUniform("spotLight.position");
//		um->setData((void*)gSpotLight.getPosition().m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("spotLight.direction");
//		um->setData((void*)gSpotLight.getDirection().m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("spotLight.ambient");
//		um->setData((void*)gSpotLight.getColor(PC_AMBIENT).m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("spotLight.diffuse");
//		um->setData((void*)gSpotLight.getColor(PC_DIFFUSE).m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("spotLight.specular");
//		um->setData((void*)gSpotLight.getColor(PC_SPECULAR).m, 3 * sizeof(float));
//		um = lightingLayout->getProgram()->getUniform("spotLight.constant");
//		um->setValue(gSpotLight.getAttenuationConstant());
//		um = lightingLayout->getProgram()->getUniform("spotLight.linear");
//		um->setValue(gSpotLight.getAttenuationLinear());
//		um = lightingLayout->getProgram()->getUniform("spotLight.quadratic");
//		um->setValue(gSpotLight.getAttenuationQuadratic());
//		um = lightingLayout->getProgram()->getUniform("spotLight.outerSpot");
//		um->setValue(gSpotLight.getSpotOutter());
//		um = lightingLayout->getProgram()->getUniform("spotLight.innerSpot");
//		um->setValue(gSpotLight.getSpotInner());
//
//		for (int i = 0; i < 10; ++i)
//		{
//			Mat4 model;
//			model.makeTranslate(cubePositions[i]);
//			model.rotate(Vec3(1.0f, 0.3f, 0.5f), 20.0f * i * Math::PI / 180);
//
//			um = lightingLayout->getProgram()->getUniform("iModel");
//			um->setData(model.ptr(), 16 * sizeof(float));
//
//			lightingLayout->getProgram()->bindUniforms();
//			renderEngine->render(lightingLayout);
//		}
//
//		lampLayout->getProgram()->bind();
//		um = lampLayout->getProgram()->getUniform("iCamera");
//		um->setData(vpm.ptr(), 16 * sizeof(float));
//		for (int i = 0; i < 4; ++i)
//		{
//			Mat4 model;
//			model.makeTranslate(gPointLights[i].getPosition());
//			model.scale(Vec3(0.2f, 0.2f, 0.2f));
//			um = lampLayout->getProgram()->getUniform("iModel");
//			um->setData(model.ptr(), 16 * sizeof(float));
//
//			lampLayout->getProgram()->bindUniforms();
//			renderEngine->render(lampLayout);
//		}
//		
//
//		// swap the buffers
//		renderEngine->getCurrentRenderWindow()->swapBuffers();
//	}
//
//	BLADE_DELETE(gCamera);
//
//	BLADE_DELETE(pTexture);
//	BLADE_DELETE(pTexture2);
//
//	BLADE_DELETE(lightingProgram);
//	BLADE_DELETE(lampProgram);
//	BLADE_DELETE(vbo);
//
//	lightingLayout->destroy();
//	BLADE_DELETE(lightingLayout);
//
//	lampLayout->destroy();
//	BLADE_DELETE(lampLayout);
//
//	renderEngine->destroy();
//	BLADE_DELETE(renderEngine);
//
//	return 0;
//}