#include "FPSCamera.h"

FPSCamera::FPSCamera(Display* window, glm::vec3& position, float fov, float aspect, float near, float far) : Camera(window, fov, aspect, near, far)
{
	m_position = position;
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	m_target = glm::vec3(0.0f, 0.0f, -1.0f);
	m_velocity = 0.0f;
	m_viewFriction = 0.0f;
	m_moveFriction = 0.85f;

	m_moveSpeed = 0.1f;
	m_maxSpeed = 0.1f;
	m_sensitivity = 0.1f;

	m_keys["FORWARD"] = SDLK_z;
	m_keys["BACKWARD"] = SDLK_s;
	m_keys["LEFT"] = SDLK_q;
	m_keys["RIGHT"] = SDLK_d;
	m_keys["UP"] = SDLK_e;
	m_keys["DOWN"] = SDLK_a;


	m_keys_states["FORWARD"] = false;
	m_keys_states["BACKWARD"] = false;
	m_keys_states["LEFT"] = false;
	m_keys_states["RIGHT"] = false;
	m_keys_states["UP"] = false;
	m_keys_states["DOWN"] = false;

	//this->setIsActive(true);
	//this->lockCursor(true);
}

void FPSCamera::lockCursor(bool value)
{
	if (value == true)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_WarpMouseInWindow(
			this->getWindow()->getWindow(),
			(int)(this->getWindow()->getSize().x * 0.5f), 
			(int)(this->getWindow()->getSize().y * 0.5f)
		);
	}
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

void FPSCamera::move(Direction dir)
{
	if (this->getMode() == PERSPECTIVE)
	{
		float speed = m_moveSpeed * (float)m_delta;

		switch (dir)
		{
			case UP:
				m_positionDelta += m_up * speed;
				break;
			case DOWN:
				m_positionDelta -= m_up * speed;
				break;
			case LEFT:
				m_positionDelta -= glm::cross(m_direction, m_up) * speed;
				break;
			case RIGHT:
				m_positionDelta += glm::cross(m_direction, m_up) * speed;
				break;
			case FORWARD:
				m_positionDelta += m_direction * speed;
				break;
			case BACKWARD:
				m_positionDelta -= m_direction * speed;
				break;
		}
	}
}

void FPSCamera::setPitch(float degrees)
{
	m_pitch -= degrees;

	if (m_pitch > 360.0f)
		m_pitch -= 360.0f;
	else if (m_pitch < -360.0f)
		m_pitch += 360.0f;
}

void FPSCamera::setYaw(float degrees)
{
	m_yaw -= degrees;

	if (m_yaw > 360.0f)
		m_yaw -= 360.0f;
	else if (m_yaw < -360.0f)
		m_yaw += 360.0f;
}

void FPSCamera::update(double delta)
{
	if (this->isActive())
	{
		if (m_keys_states["FORWARD"])
			this->move(FORWARD);
		if (m_keys_states["BACKWARD"])
			this->move(BACKWARD);
		if (m_keys_states["LEFT"])
			this->move(LEFT);
		if (m_keys_states["RIGHT"])
			this->move(RIGHT);
		if (m_keys_states["UP"])
			this->move(UP);
		if (m_keys_states["DOWN"])
			this->move(DOWN);
	}

	m_delta = delta;
	m_direction = glm::normalize(m_target - m_position);

	if (this->getMode() == ORTHOGRAPHIC)
	{
		this->setProjectionMatrix(glm::ortho(-1.5f * this->getAspect(), 1.5f * this->getAspect(), -1.5f, 1.5f, -10.0f, 10.f));
	}
	else if (this->getMode() == PERSPECTIVE)
	{
		this->setProjectionMatrix(glm::perspective(this->getFov(), this->getAspect(), this->getNear(), this->getFar()));

		glm::vec3 axis = glm::cross(m_direction, m_up);
		glm::quat pitch = m_pitch * axis;

		glm::quat yaw = m_yaw * m_up;
		glm::quat rot = glm::cross(pitch, yaw);
		rot = glm::normalize(rot);

		m_direction = glm::rotate(rot, m_direction);
		m_position += m_positionDelta;
		m_target = m_position + m_direction;

		m_yaw *= m_viewFriction;
		m_pitch *= m_viewFriction;

		m_positionDelta = m_positionDelta * m_moveFriction;
	}

	this->setViewMatrix(glm::lookAt(m_position, m_target, m_up));
}

void FPSCamera::onKeyDown(const SDL_Keycode& keycode)
{
	for (const auto &key : m_keys)
		if (keycode == key.second)
			m_keys_states[key.first] = true;
}

void FPSCamera::onKeyUp(const SDL_Keycode& keycode)
{
	for (const auto &key : m_keys)
		if (keycode == key.second)
			m_keys_states[key.first] = false;
}

void FPSCamera::onMouseMove(const glm::vec2& mouse)
{
	if (this->isActive())
	{
		this->setPitch(mouse.y * ((float)m_delta * m_sensitivity));
		this->setYaw(mouse.x * ((float)m_delta * m_sensitivity));
	}
}

void FPSCamera::onMouseDown(Uint8 button)
{
	if (button == SDL_BUTTON_RIGHT)
	{
		this->lockCursor(true);
		this->setActive(true);
	}
}

void FPSCamera::onMouseUp(Uint8 button)
{
	if (button == SDL_BUTTON_RIGHT)
	{
		this->lockCursor(false);
		this->setActive(false);
	}
}

void FPSCamera::onMouseWheel(const SDL_Event& event)
{
	m_moveSpeed += event.wheel.y * 0.01f;

	if (m_moveSpeed < 0)
		m_moveSpeed = 0;
}

FPSCamera::~FPSCamera()
{

}
