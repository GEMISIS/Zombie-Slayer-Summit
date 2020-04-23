#include <Windows.h>
#include <GL/glew.h>

#include "graphics/ObjLoader.h"

ObjLoader::ObjLoader(Shader* shader, std::string fileName) : Drawable()
{
	this->elementID = 0;
	this->file.open(fileName, std::ios::in);
	if (this->file)
	{
		std::string line;
		while (std::getline(this->file, line))
		{
			std::istringstream stringStream(line.substr(1));
			switch (line[0])
			{
			case '#':
				// Comment, ignore
				break;
			case 'v':
				float x, y, z;
				stringStream >> x >> y >> z;
				this->HandleVertexData(line, x, y, z);
				break;
			case 'f':
				std::string triplet;
				while (stringStream >> triplet)
				{
					this->HandleFaceData(triplet);
				}
				break;
			}
		}

		this->bindVAO();
		this->loadVertices(this->finalData);
		this->loadElements(this->elements);
		this->positionAttribute = shader->getAttribute("position");
		this->colorAttribute = shader->getAttribute("color");
		this->uvAttribute = shader->getAttribute("uv");

		glEnableVertexAttribArray(this->positionAttribute);
		glVertexAttribPointer(this->positionAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(this->colorAttribute);
		glVertexAttribPointer(this->colorAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->uvAttribute);
		glVertexAttribPointer(this->uvAttribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		this->unbindVAO();

		this->vertices.clear();
		this->uvs.clear();
		this->finalData.clear();
		this->elements.clear();
		this->elementsCache.clear();
		this->dataStream.clear();
		this->file.close();
	}
}

void ObjLoader::HandleFaceData(std::string triplet)
{
	float v, vt, vn;
	std::istringstream stringStream(triplet);
	std::string token;
	std::getline(stringStream, token, '/');
	v = std::stoul(token, 0, 10);
	std::getline(stringStream, token, '/');
	vt = std::stoul(token, 0, 10);
	std::getline(stringStream, token, '/');
	vn = std::stoul(token, 0, 10);

	{
		std::string elementString = std::to_string(v) + std::to_string(vt) + std::to_string(vn);
		auto element = this->elementsCache.find(elementString);
		if (element != this->elementsCache.end())
		{
			elements.emplace_back(element->second);
		}
		else
		{
			v -= 1;
			vt -= 1;
			vn -= 1;
			for (int i = 0; i < 3; i++)
			{
				finalData.emplace_back(this->vertices[v * 3 + i]);
			}
			finalData.emplace_back(elementID / 256.0f);
			finalData.emplace_back(1);
			finalData.emplace_back(1);
			for (int i = 0; i < 2; i++)
			{
				finalData.emplace_back(this->uvs[vt * 2 + i]);
			}
			this->elements.emplace_back(elementID);
			this->elementsCache.emplace(elementString, elementID);
			elementID += 1;
		}
	}
}

void ObjLoader::HandleVertexData(std::string type, float x, float y, float z)
{
	switch (type[1])
	{
	case 't':
		this->uvs.push_back(x);
		this->uvs.push_back(y);
		break;
	case ' ':
		this->vertices.push_back(x);
		this->vertices.push_back(y);
		this->vertices.push_back(z);
		break;
	}
}