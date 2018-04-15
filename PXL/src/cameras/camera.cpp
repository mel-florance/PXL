#include "camera.h"

Camera::Camera(Display* window, float fov = 70.0f, float aspect = 16.0f / 9.0f, float near = 0.01f, float far = 1000.0f) :
	m_window(window),
	m_fov(fov),
	m_aspect(aspect),
	m_near(near),
	m_far(far),
	m_active(false),
	m_mode(PERSPECTIVE)
{
	m_projMatrix = glm::perspective(fov, aspect, near, far);
}

void Camera::onWindowResized(const SDL_Event& event)
{
	if (m_window != nullptr)
		this->setAspect((float)m_window->getAspect());
}

void Camera::onWindowSizeChanged(const SDL_Event& event)
{
	if (m_window != nullptr)
		this->setAspect((float)m_window->getAspect());
}

Camera::~Camera()
{

}
