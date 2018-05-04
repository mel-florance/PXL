
#include "camera.h"
#include "display.h"
#include "viewport.h"

 Camera::Camera(Display & window, float fov, float aspect, float near, float far) {

	m_projMatrix = glm::perspective(fov, aspect, near, far);
}

 Camera::~Camera() {


}

void Camera::onWindowResized(const SDL_Event & event) {

	if (m_window != nullptr)
		this->setAspect((float)m_window->getAspect());
}

void Camera::onWindowSizeChanged(const SDL_Event & event) {

	if (m_window != nullptr)
		this->setAspect((float)m_window->getAspect());
}

