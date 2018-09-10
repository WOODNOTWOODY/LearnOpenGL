#include "CoreStd.h"
#include "Light.h"

BLADE_NAMESPACE_BEGIN

Light::Light(LightType type)
	: m_type(type)
{
	m_color[PC_AMBIENT] = COLOR_WHITE;
	m_color[PC_DIFFUSE] = COLOR_WHITE;
	m_color[PC_SPECULAR] = COLOR_WHITE;
}

Light::~Light()
{
}

DirectionalLight::DirectionalLight()
	: Light(LT_DIRECTIONAL_LIGHT)
{
}

DirectionalLight::~DirectionalLight()
{
}

PointLight::PointLight()
	: Light(LT_POINT_LIGHT)
{
}

PointLight::~PointLight()
{
}

void PointLight::setAttenuation(float range, float constant, float linear, float quadratic)
{
	m_range = range;
	m_attenuationConstant = constant;
	m_attenuationLinear = linear;
	m_attenuationQuadratic = quadratic;
}

SpotLight::SpotLight()
	: Light(LT_SPOT_LIGHT)
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::setAttenuation(float range, float constant, float linear, float quadratic)
{
	m_range = range;
	m_attenuationConstant = constant;
	m_attenuationLinear = linear;
	m_attenuationQuadratic = quadratic;
}

BLADE_NAMESPACE_END