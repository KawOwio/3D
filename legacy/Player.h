#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <iostream>

class Player
{
private:
	glm::vec3 position;
	glm::vec3 oldPosition;

	float yaw;
	float pitch;
	float playerSpeed;

	glm::vec2 m_oldMousePos;
	glm::vec2 m_mousePos;

	//Bool if key was pressed
	bool w;
	bool a;
	bool s;
	bool d;

public:
	Player();
	~Player();

	bool keyboardInput(SDL_Event event, float speed, glm::vec3 front);
	void mouseInput(SDL_Event);
	void move(glm::vec3 fwd, glm::vec3 right, bool collision);

	glm::vec3 getPosition();

	float getYaw();
	float getPitch();

	void setPosition(glm::vec3 _pos);
};