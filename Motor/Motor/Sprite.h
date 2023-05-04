#pragma once
#include <GL/glew.h>
#include <vector>
#include "Vertex.h"
using namespace std;
class Sprite
{
private:
	float x;
	float y;
	float width;
	float height;
	vector<Vertex> vertex_vector;
	GLuint vboID;
public:
	Sprite();
	~Sprite();
	void init(float x, float y, float width, float height);
	void draw();
};

