#include "Player.h"

Player::Player()
{
	//m_position = glm::vec3(0.0f, -1.3f, -10.0f);
	m_position = glm::vec3(0.5f, 0.0f, 0.0f);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

Player::~Player()
{

}

void Player::keyboardInput(SDL_Event event, float speed)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w: m_velocity.z -= speed; break;
		case SDLK_s: m_velocity.z += speed; break;
		case SDLK_a: m_velocity.x -= speed; break;
		case SDLK_d: m_velocity.x += speed; break;

		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w: m_velocity.z += speed; break;
		case SDLK_s: m_velocity.z -= speed; break;
		case SDLK_a: m_velocity.x += speed; break;
		case SDLK_d: m_velocity.x -= speed; break;
		}
	}
}

glm::vec2 Player::mouseInput(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		m_mousePos.x += event.motion.xrel * 10.0f;
		m_mousePos.y += event.motion.yrel * 10.0f;
	}

	glm::vec2 deltaMousePos = m_oldMousePos - m_mousePos;
	m_oldMousePos = m_mousePos;
	std::cout << deltaMousePos.x << " <X Y> " << deltaMousePos.y << std::endl;
	return deltaMousePos;
}

void Player::move(glm::vec3 _forward)
{
	m_position += m_velocity;
}

void Player::setPosition(glm::vec3 _pos)
{
	m_position += _pos;
}

glm::vec3 Player::getPosition()
{
	return m_position;
}