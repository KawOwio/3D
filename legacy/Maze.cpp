#include "Maze.h"

Maze::Maze()
{

}

Maze::~Maze()
{

}

void Maze::MazeInit(std::string _mazeFile, glm::vec2 _windowSize)
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
			maze[r][c].pos = glm::vec3(dimensions * r, 0, dimensions * c);

			std::cout << "R: " << r << "\tC: " << c << "\tPos: " << maze[r][c].pos.x << " " << maze[r][c].pos.z << std::endl;
		}
	}
}

void Maze::Draw()
{

}

int Maze::GetSpaceStatus(int _rows, int _columns)
{
	return maze[_rows][_columns].space;
}

glm::vec3 Maze::GetSpacePosition(int _rows, int _columns)
{
	return maze[_rows][_columns].pos;
}