#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <exception>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if(!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if(glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	VertexBuffer *positions = new VertexBuffer();
	positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
	positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
	positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

	VertexBuffer *texCoords = new VertexBuffer();
	texCoords->add(glm::vec2(0.5f, 0.0f));
	texCoords->add(glm::vec2(0.0f, 1.0f));
	texCoords->add(glm::vec2(1.0f, 1.0f));

	VertexArray *shape = new VertexArray();
	shape->SetBuffer("in_Position", positions);
	shape->SetBuffer("in_TexCoord", texCoords);

	ShaderProgram *shaderProgram = new ShaderProgram("../shaders/simple.vert", "../shaders/simple.frag");
	float angle = 0.0f;

	//Lab6
	int w, h, channels = 0;
	unsigned char *data = stbi_load("image.png", &w, &h, &channels, 4);

	if (!data)
	{
		throw std::exception();
	}

	 //Create and bind a texture
	GLuint textureId = 0;
	glGenTextures(1, &textureId);

	if (!textureId)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	//Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//Free the loaded data
	free(data);
	//Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);
	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	bool quit = false;

	while(!quit)
	{
		SDL_Event event = {0};

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, textureId);
		shaderProgram->SetUniformFloat("in_Texture", 1);

		//Draw with perspective projection matrix////////////
		shaderProgram->SetUniformMat4("in_Projection", glm::perspective(glm::radians(45.0f),
			(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -2.5f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1, 1, 0));

		shaderProgram->SetUniformMat4("in_Model", model);
		shaderProgram->draw(shape);
		/////////////////////////////////////////////////////

		//Draw with orthographic projection matrix///////////
		shaderProgram->SetUniformMat4("in_Projection", glm::ortho(0.0f, (float)WINDOW_WIDTH,
			0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f));

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
		model = glm::scale(model, glm::vec3(100, 100, 1));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1));

		shaderProgram->SetUniformMat4("in_Model", model);
		shaderProgram->draw(shape);
		/////////////////////////////////////////////////////

		angle += 1.0f;
		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}