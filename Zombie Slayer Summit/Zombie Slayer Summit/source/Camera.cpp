#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <Windows.h>
#include <GL/glew.h>
#include "graphics/Shader.h"

#include "Camera.h"

Camera::Camera(Shader* shader)
{
	this->shader = shader;
	this->vpUniform = this->shader->getUniformLocation("vp");
	this->projectMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
}

void Camera::SetShader(Shader* shader)
{
	this->shader = shader;
	this->vpUniform = this->shader->getUniformLocation("vp");
}

void Camera::SetTranslation(float x, float y, float z)
{
	this->translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	this->UpdateWorldMatrix();
}

void Camera::SetRotation(float rotation, float x, float y, float z)
{
	this->rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(x, y, z));
	this->UpdateWorldMatrix();
}

void Camera::Translate(float x, float y, float z)
{
	this->translation = glm::translate(this->translation, glm::vec3(x, y, z));
	this->UpdateWorldMatrix();
}

void Camera::Rotate(float rotation, float x, float y, float z)
{
	this->rotation = glm::rotate(this->rotation, glm::radians(rotation), glm::vec3(x, y, z));
	this->UpdateWorldMatrix();
}

void Camera::Update()
{
	this->shader->SetUniformMatrix(this->vpUniform, this->projectMatrix * this->viewMatrix);
}

void Camera::UpdateWorldMatrix()
{
	this->viewMatrix = this->rotation * this->translation;
}





