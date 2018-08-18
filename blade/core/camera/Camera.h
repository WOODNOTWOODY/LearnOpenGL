#ifndef __BLADE_CAMERA_H__
#define __BLADE_CAMERA_H__

#include "math/Mat4.h"

BLADE_NAMESPACE_BEGIN

enum CamProjMode
{
	CPM_PERSPECTIVE,
	CPM_ORTHO,
};

class BLADE_CORE_API Camera
{
public:
	Camera(CamProjMode mode);
	~Camera();

public:
	inline void             setPosition(const Vec3& pos) { m_position = pos; m_bRecalcView = true; }
	void                    move(const Vec3& offset);
	inline Vec3             getPosition() const { return m_position; }

	inline void             setDirection(const Vec3& dir) { m_direction = dir; m_bRecalcView = true; }
	void                    rotate(const Vec3& axis, float angle);
	void                    lookAt(const Vec3& pos);
	inline Vec3             getDirection() const { return m_direction; }

	inline void             setFov(float fov) { m_fov = fov; m_bRecalcProj = true; }
	inline float            getFov() const { return m_fov; }

	inline void             setWidth(uint32 width) { m_width = width; m_bRecalcProj = true; }
	inline void             setHeight(uint32 height) { m_height = height; m_bRecalcProj = true; }
	inline float            getAspectRatio() const { return m_aspectRatio; }

	inline void             setNearAndFarClip(float nearClip, float farClip)
	{
		assert(nearClip > 0.0f);
		assert(nearClip < farClip);
		m_nearClip = nearClip;
		m_farClip = farClip;
		m_bRecalcProj = true;
	}
	inline float            getNearClip() const { return m_nearClip; }
	inline float            getFarClip() const { return m_farClip; }

	inline const Mat4&      getViewMatrix() { updateView(); return m_matView; }
	inline const Mat4&      getProjMatrix() { updateProj(); return m_matProj; }
	inline const Mat4       getViewProjMatrix() { updateView(); updateProj(); return m_matProj * m_matView; }

	inline const Vec3&      getRight() const { return m_right; }
	inline const Vec3&      getUp() const { return m_up; }

	void                    update();

private:
	void                    updateView();
	void                    updateProj();

private:
	Vec3          m_position;
	Vec3          m_direction;
	float         m_fov;
	uint32        m_width;
	uint32        m_height;
	float         m_aspectRatio;
	float         m_nearClip;
	float         m_farClip;
	CamProjMode   m_projMode;

	bool          m_bRecalcView;
	bool          m_bRecalcProj;
	Mat4          m_matView;
	Mat4          m_matProj;
	Mat4          m_matVP;
	Vec3          m_up;
	Vec3          m_right;
};

BLADE_NAMESPACE_END

#endif
