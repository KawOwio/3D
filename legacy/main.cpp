#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Maze.h"
#include "Player.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

#include <exception>

int windowWidth = 800;
int windowHeight = 600;

float playerSpeed = 5.0f;
int FPS = 60;
int frameStartMs = 0;

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Maze Game",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    windowWidth, windowHeight,
	  SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if(!SDL_GL_CreateContext(window))
  {
    throw std::exception();
  }

  if(glewInit() != GLEW_OK)
  {
    throw std::exception();
  }

  VertexArray *hallShape = new VertexArray("../re_hall_baked.obj");
  Texture *hallTexture = new Texture("../re_hall_diffuse.png");
  VertexArray *shape = new VertexArray("../lumberJack.obj");
  Texture *texture = new Texture("../lumberJack_diffuse.png");
  VertexArray *cube = new VertexArray("../cube.obj");
  Texture *cubeTexture = new Texture("../cube2.png");

  ShaderProgram *shader = new ShaderProgram("../shaders/simple.vert", "../shaders/simple.frag");

  Maze mazeInit;
  Player myPlayer;
  mazeInit.MazeInit("../21x21.txt", glm::vec2(800, 600));

  bool quit = false;
  bool init = true;

  glm::vec2 angle = glm::vec2(0.0f, 0.0f);
  float speed = playerSpeed / FPS;
  float lastTime = SDL_GetTicks();

  float test = 0.0f;

  glm::vec2 cameraRotation;
  

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  SDL_SetRelativeMouseMode(SDL_TRUE);
  while(!quit)
  {
	frameStartMs = SDL_GetTicks();
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
	  myPlayer.keyboardInput(event, speed);
	  
    }
	cameraRotation = myPlayer.mouseInput(event);
	angle += cameraRotation;

	if (init == true)
	{
		//Make maze here
		init = false;
	}

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw with perspective projection matrix
    shader->setUniform("in_Projection", glm::perspective(glm::radians(60.0f),
     (float)windowWidth / (float)windowHeight, 0.1f, 100.f));

    // Create a "camera"
    glm::mat4 model(1.0f); 
	model = glm::rotate(model, glm::radians(angle.x / 10.0f), glm::vec3(0, 1, 0));
	//model = glm::rotate(model, glm::radians(angle.y / 10.0f), glm::vec3(1, 0, 0));
	model = glm::translate(model, myPlayer.getPosition());

	glm::vec3 fwd = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	fwd = glm::normalize(fwd);
	myPlayer.setPosition(fwd);

	//std::cout << "XYZ: " << fwd.x << " " << fwd.y << " " << fwd.z << std::endl;
    shader->setUniform("in_View", glm::inverse(model));

    //Draw the mansion
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, -2.0f, -16.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
    shader->setUniform("in_Model", model);
    shader->setUniform("in_Texture", hallTexture);
    shader->draw(hallShape);

	//Draw the character
	/*model = glm::mat4(1.0f);
	model = glm::translate(model, myPlayer.getPosition());
	model = glm::rotate(model, glm::radians(angle.x), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);
	shader->draw(shape);*/

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.3f, -20.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", cubeTexture);
	shader->draw(cube);
	
	myPlayer.move(fwd);
    SDL_GL_SwapWindow(window);

	float time = SDL_GetTicks();
	float diff = time - lastTime;
	float deltaTime = diff / 1000.0f;
	lastTime = time;

	test += 1.0f;

	float idealTime = 1.0f / 60.0f;
	if (idealTime > deltaTime)
	{
		SDL_Delay((idealTime - deltaTime) * 1000.0f);
	}
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
