#include "Player.h"
#include <stdexcept>

FirstPirsonPlayer::FirstPirsonPlayer():
	physicsShape(glm::vec3(1.0), *this, 1),
	camera(vec3(0.0),vec3(0.0,0.0, -1.0), vec3(0.0,1.0,0.0))
{

}

const Camera& FirstPirsonPlayer::getCamera() const
{
	return camera;
}

vec3 FirstPirsonPlayer::getPosition() const
{
	return camera.pos;
}

vec3 FirstPirsonPlayer::getScale() const
{
	return vec3(1.0);
}

vec3 FirstPirsonPlayer::getRotation() const
{
	return vec3(0.0, 0.0, 0.0);
}

void FirstPirsonPlayer::setPosition(const vec3 position)
{
	camera.pos = position;
}

void FirstPirsonPlayer::setScale(const vec3 scale)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void FirstPirsonPlayer::setRotation(const vec3 rotation)
{
	throw std::logic_error("The method or operation is not implemented.");
}
