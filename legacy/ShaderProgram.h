#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>

#include "VertexArray.h"

class VertexArray;

class ShaderProgram
{
private:
	GLuint id;

public:
	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag);

	void draw(VertexArray *vertexArray);

	void SetUniformMat4(std::string uniform, glm::mat4 value);
	void SetUniformFloat(std::string uniform, float value);

	GLuint getId();
};