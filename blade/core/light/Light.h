#ifndef __BLADE_LIGHT_H__
#define __BLADE_LIGHT_H__

#include "math/Vec3.h"
#include "util/Color.h"

BLADE_NAMESPACE_BEGIN

enum PhongComponent
{
	PC_AMBIENT,
	PC_DIFFUSE,
	PC_SPECULAR,
	PC_COUNT,
};

enum LightType
{
	LT_DIRECTIONAL_LIGHT,
	LT_POINT_LIGHT,
	LT_SPOT_LIGHT,
	LT_COUNT,
};

class BLADE_CORE_API Light
{
public:
	Light(LightType type);
	virtual ~Light();

public:
	inline LightType        getType() const { return m_type; }
	inline void             setColor(PhongComponent pc, const Color& color) { m_color[pc] = color; }
	inline const Color&     getColor(PhongComponent pc) const { return m_color[pc]; }

protected:
	LightType   m_type;
	Color       m_color[PC_COUNT];
};

class BLADE_CORE_API DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();

public:
	inline void         setDirection(const Vec3& dir) { m_direction = dir; m_direction.normalize(); }
	inline const Vec3&  getDirection() const { return m_direction; }

private:
	Vec3      m_direction;
};

class BLADE_CORE_API PointLight : public Light
{
public:
	PointLight();
	~PointLight();

public:
	inline void         setPosition(const Vec3& pos) { m_position = pos; }
	inline const Vec3&  getPosition() const { return m_position; }

	inline void         setRange(float range) { m_range = range; }
	inline float        getRange() const { return m_range; }

	inline float        getAttenuationConstant() const { return m_attenuationConstant; }
	inline float        getAttenuationLinear() const { return m_attenuationLinear; }
	inline float        getAttenuationQuadratic() const { return m_attenuationQuadratic; }
	void                setAttenuation(float range, float constant, float linear, float quadratic);

private:
	Vec3     m_position;
	float    m_range;
	float    m_attenuationConstant;
	float    m_attenuationLinear;
	float    m_attenuationQuadratic;
};

class BLADE_CORE_API SpotLight : public Light
{
public:
	SpotLight();
	~SpotLight();

public:
	inline void         setPosition(const Vec3& pos) { m_position = pos; }
	inline const Vec3&  getPosition() const { return m_position; }
	inline void         setDirection(const Vec3& dir) { m_direction = dir; m_direction.normalize(); }
	inline const Vec3&  getDirection() const { return m_direction; }

	inline void         setRange(float range) { m_range = range; }
	inline float        getRange() const { return m_range; }

	inline void         setSpotOutter(float cos) { m_spotOuter = cos; }
	inline float        getSpotOutter() const { return m_spotOuter; }

	inline void         setSpotInner(float cos) { m_spotInner = cos; }
	inline float        getSpotInner() const { return m_spotInner; }

	inline float        getAttenuationConstant() const { return m_attenuationConstant; }
	inline float        getAttenuationLinear() const { return m_attenuationLinear; }
	inline float        getAttenuationQuadratic() const { return m_attenuationQuadratic; }
	void                setAttenuation(float range, float constant, float linear, float quadratic);

private:
	Vec3     m_position;
	Vec3     m_direction;
	float    m_range;
	float    m_attenuationConstant;
	float    m_attenuationLinear;
	float    m_attenuationQuadratic;
	float    m_spotOuter;
	float    m_spotInner;
};

BLADE_NAMESPACE_END

#endif
