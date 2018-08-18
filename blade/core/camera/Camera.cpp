#include "CoreStd.h"
#include "Camera.h"

BLADE_NAMESPACE_BEGIN

Camera::Camera(CamProjMode mode)
	: m_projMode(mode)
	, m_bRecalcProj(true)
	, m_bRecalcView(true)
{
	m_up = Vec3(0, 1, 0);
	m_right = Vec3(1, 0, 0);
	m_position = Vec3(0, 0, 1);
	lookAt(Vec3(0, 0, 0));

	m_width = 1.0f;
	m_height = 1.0f;
	m_aspectRatio = (float)m_width / (float)m_height;
	m_fov = Math::PI_DIV4;

	m_nearClip = 10.0f;
	m_farClip = 10000.0f;
}

Camera::~Camera()
{

}

void Camera::move(const Vec3& offset)
{
	m_position += offset;
	m_bRecalcView = true;
}

void Camera::rotate(const Vec3& axis, float angle)
{
	Mat4 rot;
	rot.makeRotate(axis, angle);
	m_direction = rot * m_direction;
	m_bRecalcView = true;
}

void Camera::lookAt(const Vec3& pos)
{
	m_direction = (m_position - pos);
	m_direction.normalize();
	m_bRecalcView = true;
}

void Camera::updateView()
{
	if (m_bRecalcView)
	{
		m_right = Vec3::Cross(m_up, m_direction);
		m_right.normalize();
		m_up = Vec3::Cross(m_direction, m_right);
		m_up.normalize();

		m_matView.m00 = m_right.x; m_matView.m01 = m_right.y; m_matView.m02 = m_right.z; m_matView.m03 = -m_right.dot(m_position);
		m_matView.m10 = m_up.x;    m_matView.m11 = m_up.y;    m_matView.m12 = m_up.z;    m_matView.m13 = -m_up.dot(m_position);
		m_matView.m20 = m_direction.x;   m_matView.m21 = m_direction.y;   m_matView.m22 = m_direction.z;   m_matView.m23 = -m_direction.dot(m_position);
		m_matView.m30 = 0;         m_matView.m31 = 0;         m_matView.m32 = 0;         m_matView.m33 = 1;

		m_bRecalcView = false;
	}
}

void Camera::updateProj()
{
	if (m_bRecalcProj)
	{
		switch (m_projMode)
		{
			case CPM_PERSPECTIVE:
			{
				m_aspectRatio = (float)m_width / (float)m_height;
				m_matProj.perspective(m_fov, m_aspectRatio, m_nearClip, m_farClip);
				break;
			}
			case CPM_ORTHO:
			{
				float halfWidth = m_width / 2.0f;
				float halfHeight = m_height / 2.0f;
				m_matProj.ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, m_nearClip, m_farClip);
				break;
			}
		}
		m_bRecalcProj = false;
	}
}

void Camera::update()
{
	updateView();
	updateProj();
}

BLADE_NAMESPACE_END