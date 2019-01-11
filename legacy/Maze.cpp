#include "Maze.h"

Maze::Maze()
{

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

			if (maze[r][c].space == 2)
			{
				startPos = maze[r][c].pos;
			}

			std::cout << "R: " << r << "\tC: " << c << "\tPos: " << maze[r][c].pos.x << " " << maze[r][c].pos.z << std::endl;
		}
	}
}

void Maze::draw(ShaderProgram *shader, VertexArray *cube, Texture *wallTexture)
{
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			//Drawing floor & ceiling
			if (maze[r][c].space == 0)
			{
				glm::vec3 temp = maze[r][c].pos;
				temp.y -= 0.5f;
				glm::mat4 model(1.0f);
				model = glm::translate(model, temp);
				model = glm::scale(model, glm::vec3(0.05f, 0.01f, 0.05f));
				shader->setUniform("in_Model", model);
				shader->setUniform("in_Texture", wallTexture);
				shader->draw(cube);

				temp.y += 13.5f;
				model = glm::mat4(1.0f);
				model = glm::translate(model, temp);
				model = glm::scale(model, glm::vec3(0.05f, 0.01f, 0.05f));
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
		}
	}
}

bool Maze::collisionCheck(glm::vec3 _pos)
{
	//TO BE FIXED
	float x = (_pos.x / dimensions);
	float z = (_pos.z / dimensions);
	x = ceil(x);
	z = ceil(z);

	std::cout << x << "< X\tZ >" << z << std::endl;

	int dx[4] = { x, x + 1, x, x - 1 };
	int dz[4] = { z - 1, z, z + 1, z };

	float left, right, top, bottom;
	

	std::cout << "Player Z: " << _pos.z << std::endl;
	//x colision
	
	if (_pos.z < maze[dx[0]][dz[0]].pos.z && maze[dx[0]][dz[0]].space == 1)
	{
		return true;
	}



	return false;
}

glm::vec3 Maze::getStartPosition()
{
	return startPos;
}

int Maze::getSpaceStatus(int _rows, int _columns)
{
	return maze[_rows][_columns].space;
}

glm::vec3 Maze::getSpacePosition(int _rows, int _columns)
{
	return maze[_rows][_columns].pos;
}