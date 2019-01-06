#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <iostream>
class Player
{
private:
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_rotation;

	glm::vec2 m_oldMousePos;
	glm::vec2 m_mousePos;

public:
	Player();
	~Player();

	void keyboardInput(SDL_Event event, float speed);
	glm::vec2 mouseInput(SDL_Event);
	void move(glm::vec3 _forward);
	
	void setPosition(glm::vec3 _pos);
	glm::vec3 getPosition();
};