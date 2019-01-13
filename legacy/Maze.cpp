#include "Maze.h"

Maze::Maze()
{
	angle = 0.0f;
	keyPick = false;
	exitStatus = false;
}

Maze::~Maze()
{

}

void Maze::mazeInit(std::string _mazeFile, glm::vec2 _windowSize)
{
	std::ifstream file(_mazeFile);

	//Check if file was open
	if (!file.is_open())
	{
		throw std::exception();
	}
	else
	{
		std::string line;
		std::getline(file, line);
		mazeInput = line;
	}
	file.close();

	//Generate maze from a text file
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			mazeTemp = mazeInput.substr(0, mazeInput.find(' '));
			mazeInput.erase(0, mazeInput.find(' ') + 1);
			maze[r][c].space = atoi(mazeTemp.c_str());
			maze[r][c].pos = glm::vec3(dimensions * r, -4.0f, dimensions * c);
			maze[r][c].cubeMin = maze[r][c].pos + glm::vec3(-4.0f, 0.0f, -4.0f);
			maze[r][c].cubeMax = maze[r][c].pos + glm::vec3(4.0f, 10.0f, 4.0f);

			if (maze[r][c].space == 2)
			{
				startPos = maze[r][c].pos;
			}
		}
	}
}

void Maze::draw(ShaderProgram *shader, VertexArray *cube, Texture *wallTexture, 
	VertexArray *ladder, Texture *ladderTexture,
	VertexArray *key, Texture *keyTexture,
	VertexArray *sign, Texture *signTexture)
{
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			//Drawing floor & ceiling
			if (maze[r][c].space == 0 || maze[r][c].space == 2 
				|| maze[r][c].space == 3 || maze[r][c].space == 4)
			{
				glm::vec3 temp = maze[r][c].pos;
				temp.y = -11.0f;
				glm::mat4 model(1.0f);
				model = glm::translate(model, temp);
				model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
				shader->setUniform("in_Model", model);
				shader->setUniform("in_Texture", wallTexture);

				shader->draw(cube);

				temp.y = +9.5f;
				model = glm::mat4(1.0f);
				model = glm::translate(model, temp);
				model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
				shader->setUniform("in_Model", model);
				shader->setUniform("in_Texture", wallTexture);
				shader->draw(cube);


			}
			//Drawing walls
			if (maze[r][c].space == 1)
			{
				glm::mat4 model(1.0f);
				model = glm::translate(model, maze[r][c].pos);
				model = glm::scale(model, glm::vec3(0.05f, 0.1f, 0.05f));
				shader->setUniform("in_Model", model);
				shader->setUniform("in_Texture", wallTexture);
				shader->draw(cube);
			}

			if (maze[r][c].space == 3)
			{

				glm::mat4 model(1.0f);
				model = glm::translate(model, maze[r][c].pos);
				model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));				
				shader->setUniform("in_Model", model);
				if (keyPick == true)
				{
					shader->setUniform("in_Texture", ladderTexture);
					shader->draw(ladder);
				}
				else
				{
					shader->setUniform("in_Texture", signTexture);
					shader->draw(sign);
				}
			}
			if (maze[r][c].space == 4)
			{
				if (keyPick == false)
				{
					glm::mat4 model(1.0f);
					glm::vec3 temp = maze[r][c].pos;
					temp.y += 6.0f;
					model = glm::translate(model, temp);
					model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
					model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1, 0, 0));
					shader->setUniform("in_Model", model);
					shader->setUniform("in_Texture", keyTexture);
					shader->draw(key);

					angle++;
				}
			}
		}
	}
}

bool Maze::collisionCheck(glm::vec3 _pos)
{
	float x = ((_pos.x - 3.3f) / dimensions);
	float z = ((_pos.z - 3.3f) / dimensions);
	x = ceil(x);
	z = ceil(z);

	int dx[4] = { x, x + 1, x, x - 1 };
	int dz[4] = { z - 1, z, z + 1, z };

	for (int i = 0; i < 4; i++)
	{
		if (maze[dx[i]][dz[i]].space == 1)
		{
			//2D AABB collision
			// add "&& (_pos.y >= maze[dx[i]][dz[i]].cubeMin.y && _pos.y <= maze[dx[i]][dz[i]].cubeMax.y)"
			// in if statement to make it into 3D
			// (not needed cause there is no Y movement in the game)
			if ((_pos.x >= maze[dx[i]][dz[i]].cubeMin.x && _pos.x <= maze[dx[i]][dz[i]].cubeMax.x)
				&& (_pos.z >= maze[dx[i]][dz[i]].cubeMin.z && _pos.z <= maze[dx[i]][dz[i]].cubeMax.z))
			{
				return true;
			}
		}
		if (maze[dx[i]][dz[i]].space == 4)
		{
			keyPick = true;
		}
		if (maze[dx[i]][dz[i]].space == 3 && keyPick == true)
		{
			exitStatus = true;
		}
	}
	return false;
}

bool Maze::getExit()
{
	return exitStatus;
}

glm::vec3 Maze::getStartPosition()
{
	return startPos;
}