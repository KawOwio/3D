#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>

#include <glm/glm.hpp>

struct Grid
{
	glm::vec3 pos;
	int space;
	bool open;
};

class Maze
{
private:
	const int size = 21;	//Inner maze is 19x19 + 2 rows and columns for walls
	//int rows, columns = size;
	const int dimensions = 16;

	std::string mazeInput;
	std::string mazeTemp;

	Grid maze[21][21];
	Grid map[20][20];

public:
	Maze();
	~Maze();

	void MazeInit(std::string _mazeFile, glm::vec2 _windowSize);

	//WIP
	void Draw();
	int GetSpaceStatus(int _rows, int _columns);
	glm::vec3 GetSpacePosition(int _rows, int _columns);
};