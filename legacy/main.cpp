//**********************************************************//
//						3D OpenGL Game						//
//			Created by Nikita Gribuska (s5065617)			//
//			GitHub link: https://github.com/s5065617/3D		//
//**********************************************************//
#include "VertexBuffer.h"
#include "Maze.h"
#include "Player.h"

#include <GL/glew.h>

#include <exception>

int windowWidth = 1280;
int windowHeight = 720;

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

  VertexArray *cube = new VertexArray("../assets/models/cube.obj");
  Texture *cubeTexture = new Texture("../assets/textures/cube.png");
  VertexArray *ladder = new VertexArray("../assets/models/ladder.obj");
  Texture *ladderTexture = new Texture("../assets/textures/ladder.jpg");
  VertexArray *key = new VertexArray("../assets/models/key.obj");
  Texture *keyTexture = new Texture("../assets/textures/key.bmp");
  VertexArray *sign = new VertexArray("../assets/models/sign.obj");
  Texture *signTexture = new Texture("../assets/textures/sign.png");

  ShaderProgram *shader = new ShaderProgram("../assets/shaders/simple.vert", "../assets/shaders/simple.frag");

  Maze maze;
  Player myPlayer;

  //Initialisation of the maze (change "21x21" to "maze" for a good debugging maze)
  maze.mazeInit("../assets/mazes/21x21.txt", glm::vec2(800, 600));

  //Getting and setting the start position
  glm::vec3 start = maze.getStartPosition();
  start.y = 4.0f;
  myPlayer.setPosition(start);

  bool quit = false;
  bool collision = false;

  float lastTime = SDL_GetTicks();
  
  glm::vec3 cameraPos = myPlayer.getPosition();
  glm::vec3 fwd = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

  float yaw = 0.0f;
  float pitch = 0.0f;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  SDL_SetRelativeMouseMode(SDL_TRUE);

  while(!quit)
  {
	frameStartMs = SDL_GetTicks();
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
		//Doesn't work for some reason?
		//works if "SDL_QUIT" changed to another event f.e. "SDL_MOUSBEBUTTONDOWN"
      if(event.type == SDL_QUIT)
      {
        quit = true;
		break;
      }
	  myPlayer.keyboardInput(event);
    }
	myPlayer.mouseInput(event);

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw with perspective projection matrix
    shader->setUniform("in_Projection", glm::perspective(glm::radians(60.0f),
     (float)windowWidth / (float)windowHeight, 0.1f, 200.f));

	//Working out forward vector
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(myPlayer.getYaw() * 0.1f), glm::vec3(0, 1, 0));
	fwd = model * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);

	//Working out right vector
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(myPlayer.getYaw() * 0.1f), glm::vec3(0, 1, 0));
	right = model * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    // Create a "camera"
    model = glm::mat4(1.0f); 
	model = glm::translate(model, myPlayer.getPosition());
	model = glm::rotate(model, glm::radians(myPlayer.getYaw() * 0.1f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(myPlayer.getPitch() * 0.1f), glm::vec3(1, 0, 0));
    shader->setUniform("in_View", glm::inverse(model));

	//Draw the maze	
	maze.draw(shader, cube, cubeTexture, ladder, ladderTexture, key, keyTexture, sign, signTexture);
	
	collision = maze.collisionCheck(myPlayer.getPosition());
	myPlayer.move(fwd, right, collision);
    SDL_GL_SwapWindow(window);

	float time = SDL_GetTicks();
	float diff = time - lastTime;
	float deltaTime = diff / 1000.0f;
	lastTime = time;
	system("cls");

	bool exit = maze.getExit();
	if (exit == true)
	{
		SDL_DestroyWindow(window);
		
		system("cls");
		std::cout << "Congratulations! You won!\n\n\n";
		SDL_Quit();
		break;
	}

	float idealTime = 1.0f / 60.0f;
	if (idealTime > deltaTime)
	{
		SDL_Delay((idealTime - deltaTime) * 1000.0f);
	}
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  system("pause");
  return 0;
}
