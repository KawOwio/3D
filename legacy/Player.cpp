#include "Player.h"

Player::Player()
{
	//m_position = glm::vec3(0.0f, -1.3f, -10.0f);
	m_position = glm::vec3(0.0f, 4.0f, 1.0f);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
}

Player::~Player()
{

}

bool Player::keyboardInput(SDL_Event event, float speed, glm::vec3 front, glm::vec3 up)
{

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		//case SDLK_w: m_velocity.z -= speed; break;
		//case SDLK_s: m_velocity.z += speed; break;
		//case SDLK_a: m_velocity.x -= speed; break;
		//case SDLK_d: m_velocity.x += speed; break;
		//case SDLK_w: m_velocity += speed; break;
		//case SDLK_s: m_velocity -= speed; break;
		//case SDLK_a: m_velocity -= speed; break;
		//case SDLK_d: m_velocity += speed; break;
		case SDLK_w: w = true; break;
		case SDLK_s: s = true; break;
		case SDLK_a: a = true; break;
		case SDLK_d: d = true; break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		//case SDLK_w: m_velocity = glm::vec3(0.0f, 0.0f, 0.0f); break;
		//case SDLK_s: m_velocity = glm::vec3(0.0f, 0.0f, 0.0f); break;
		//case SDLK_a: m_velocity = glm::vec3(0.0f, 0.0f, 0.0f); break;
		//case SDLK_d: m_velocity = glm::vec3(0.0f, 0.0f, 0.0f); break;
		case SDLK_w: w = false; break;
		case SDLK_s: s = false; break;
		case SDLK_a: a = false; break;
		case SDLK_d: d = false; break;
		}
	}
	return false;
}

void Player::UpdateView(glm::vec3 fwd)
{
	glm::mat4 matPitch = glm::mat4(1.0f);
	glm::mat4 matYaw = glm::mat4(1.0f);

	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 rotate = matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -fwd);

	viewMatrix = rotate * translate;
}

glm::vec2 Player::mouseInput(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		m_mousePos.x += event.motion.xrel * 10.0f;
		m_mousePos.y += event.motion.yrel * 10.0f;
	}

	glm::vec2 deltaMousePos = m_oldMousePos - m_mousePos;

	yaw += deltaMousePos.x;
	pitch += deltaMousePos.y;

	float angle = 45.0f * 10.0f;

	if (pitch > angle)
	{
		pitch = angle;
	}
	else if (pitch < -angle)
	{
		pitch = -angle;
	}

	m_oldMousePos = m_mousePos;
	std::cout << deltaMousePos.x << " <X Y> " << deltaMousePos.y << std::endl;
	return deltaMousePos;
}

void Player::move(glm::vec3 fwd, glm::vec3 right, bool collision)
{
	playerSpeed = 0.2f;
	
	if (!collision)
	{
		if (w == true)
		{
			m_position += playerSpeed * fwd;
		}
	}
	else
	{
		if (w == true)
		{
			m_position -= playerSpeed * fwd;
		}
	}

	if (s == true)
	{
		m_position -= playerSpeed * fwd;
	}
	if (a == true)
	{
		m_position -= playerSpeed * right;
	}
	if (d == true)
	{
		m_position += playerSpeed * right;
	}

	std::cout << "X: " << m_position.x <<
				"\nY: " << m_position.y <<
				"\nZ: " << m_position.z << std::endl;
}

glm::vec3 Player::getPosition()
{
	return m_position;
}

glm::mat4 Player::getViewMatrix()
{
	return viewMatrix;
}

float Player::getYaw()
{
	return yaw;
}

float Player::getPitch()
{
	return pitch;
}

void Player::setPosition(glm::vec3 _pos)
{
	m_position = _pos;
}