#include "camera.h"

Camera::Camera(float fov, float aspect, float near, float far)
{
	m_projMatrix = glm::perspective(fov, aspect, near, far);
}

Camera::~Camera()
{

}