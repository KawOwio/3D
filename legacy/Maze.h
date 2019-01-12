#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Texture.h"

struct Grid
{
	glm::vec3 pos;
	glm::vec3 cubeMin;
	glm::vec3 cubeMax;
	int space;
	bool open;
};

class Maze
{
private:
	const int size = 21;	//Inner maze is 19x19 + 2 rows and columns for walls
	//int rows, columns = size;
	const float dimensions = 7.0f;

	std::string mazeInput;
	std::string mazeTemp;

	glm::vec3 startPos;

	Grid maze[21][21];
	Grid map[21][21];

public:
	Maze();
	~Maze();

	void mazeInit(std::string _mazeFile, glm::vec2 _windowSize);

	//WIP
	void draw(ShaderProgram *shader, VertexArray *cube, Texture *wallTexture);
	bool collisionCheck(glm::vec3 _pos);
	glm::vec3 getStartPosition();

	//??
	int getSpaceStatus(int _rows, int _columns);
	glm::vec3 getSpacePosition(int _rows, int _columns);
};