#pragma once
#include "Camera.h"
#include "GameObject.h"
#include "BoxPhysicsShape.h"

class FirstPirsonPlayer : public GameObject
{
public:
	FirstPirsonPlayer();
	const Camera& getCamera() const;
	vec3 getPosition() const override;
	vec3 getScale() const override;
	vec3 getRotation() const override;
	void setPosition(const vec3 position) override;
	void setScale(const vec3 scale) override;
	void setRotation(const vec3 rotation) override;
private:
	Camera camera;
	BoxPhysicsShape physicsShape;
};