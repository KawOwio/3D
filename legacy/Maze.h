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
	int space;	//0-4, initialising what is going to be on a specific tile
				//0 - open space
				//1 - wall
				//2 - start position
				//3 - end position
				//4 - a key
};

class Maze
{
private:
	const int size = 21;	//Inner maze is 19x19 + 2 rows and columns for walls
	const float dimensions = 7.0f;	//x and z dimensions of walls (2 * dimensions for walls)

	float angle;	//for key rotation

	//For initialising the maze from a text file
	std::string mazeInput;
	std::string mazeTemp;

	glm::vec3 startPos;	//Start position of a player

	Grid maze[21][21];	//Structure representing the maze itself

	bool keyPick;	//is key picked?
	bool exitStatus;	//is finish reached?

public:
	Maze();
	~Maze();

	void mazeInit(std::string _mazeFile, glm::vec2 _windowSize);
	void draw(ShaderProgram *shader, VertexArray *cube, Texture *wallTexture, 
		VertexArray *ladder, Texture *ladderTexture,
		VertexArray *key, Texture *keyTexture,
		VertexArray *sign, Texture *signTexture);
	bool collisionCheck(glm::vec3 _pos);
	bool getExit();
	glm::vec3 getStartPosition();
};