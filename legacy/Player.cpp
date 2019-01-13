#include "Player.h"

Player::Player()
{
	pitch = 40.0f;
	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
}

Player::~Player()
{

}

bool Player::keyboardInput(SDL_Event event, float speed, glm::vec3 front)
{

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
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
		case SDLK_w: w = false; break;
		case SDLK_s: s = false; break;
		case SDLK_a: a = false; break;
		case SDLK_d: d = false; break;
		}
	}
	return false;
}

void Player::mouseInput(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		m_mousePos.x += event.motion.xrel * 10.0f;
		m_mousePos.y += event.motion.yrel * 10.0f;
	}

	glm::vec2 deltaMousePos = m_oldMousePos - m_mousePos;

	yaw += deltaMousePos.x;
	pitch += deltaMousePos.y;

	float angle = 90.0f * 10.0f;

	if (pitch > angle)
	{
		pitch = angle;
	}
	else if (pitch < -angle)
	{
		pitch = -angle;
	}

	m_oldMousePos = m_mousePos;
}

void Player::move(glm::vec3 fwd, glm::vec3 right, bool collision)
{
	playerSpeed = 0.2f;

	if (!collision)
	{
		if (w == true)
		{
			oldPosition = position;
			position += playerSpeed * fwd;
		}
		if (s == true)
		{
			oldPosition = position;
			position -= playerSpeed * fwd;			
		}
		if (a == true)
		{
			oldPosition = position;
			position -= playerSpeed * right;
			
		}
		if (d == true)
		{
			oldPosition = position;
			position += playerSpeed * right;
			
		}
	}
	else
	{
		position = oldPosition;
	}

	std::cout << "X: " << position.x <<
				"\nY: " << position.y <<
				"\nZ: " << position.z << std::endl;
}

glm::vec3 Player::getPosition()
{
	return position;
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
	position = _pos;
}