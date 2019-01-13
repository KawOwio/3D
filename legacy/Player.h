#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <iostream>

class Player
{
private:
	glm::vec3 position;
	glm::vec3 oldPosition;
	glm::vec3 tempPosition;
	glm::vec3 velocity;

	float yaw;
	float pitch;
	float playerSpeed;

	glm::mat4 viewMatrix;

	glm::vec2 m_oldMousePos;
	glm::vec2 m_mousePos;

	bool w;
	bool a;
	bool s;
	bool d;

public:
	Player();
	~Player();

	bool keyboardInput(SDL_Event event, float speed, glm::vec3 front, glm::vec3 up);
	void UpdateView(glm::vec3 fwd);
	void mouseInput(SDL_Event);
	void move(glm::vec3 fwd, glm::vec3 right, bool collision);

	glm::vec3 getPosition();
	glm::mat4 getViewMatrix();

	float getYaw();
	float getPitch();

	void setPosition(glm::vec3 _pos);
};