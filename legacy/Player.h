#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <iostream>
class Player
{
private:
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_rotation;

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
	glm::vec2 mouseInput(SDL_Event);
	void move(glm::vec3 fwd, glm::vec3 right, bool collision);

	glm::vec3 getPosition();
	glm::mat4 getViewMatrix();

	float getYaw();
	float getPitch();

	void setPosition(glm::vec3 _pos);
};