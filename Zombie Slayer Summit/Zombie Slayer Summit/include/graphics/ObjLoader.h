#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "Shader.h"

class ObjLoader : public Drawable
{
public:
	ObjLoader(Shader* shader, std::string fileName);
private:
	void HandleVertexData(std::string type, float x, float y, float z);
	void HandleFaceData(std::string triplet);
	std::ifstream file;
	std::string fileName;
	std::stringstream dataStream;
	std::vector<float> vertices;
	std::vector<float> uvs;
	std::vector<float> finalData;
	std::vector<unsigned int> elements;
	std::unordered_map<std::string, unsigned int> elementsCache;
	GLuint textureID;
	unsigned int elementID;
	GLint positionAttribute, uvAttribute, colorAttribute;
};