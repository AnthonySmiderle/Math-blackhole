#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class C_Circle
{
public:
	C_Circle(Scene* parentScene, Vec2 position, Vec2 offset, float radius,float mass, Color4F color);
	~C_Circle();

	void setPosition(Vec2 position);

	void update(float dt);

	Vec2 getPosition() const {
		return position;
	}
	float getRadius() const {
		return radius;
	}

	Vec2 getVelocity() const;
	Vec2 getAccel() const;
	Vec2 getForce() const;
	float getMass() const;

	void setVelocity(Vec2);
	void setAccel(Vec2);
	void setForce(Vec2);
	void setMass(float);

private:
	Scene* parentScene = nullptr;
	DrawNode* drawNode = nullptr;

	float mass;
	Vec2 velocity;
	Vec2 acceleration;
	Vec2 force;

	Vec2 position;
	Vec2 offset;
	float radius;
	Color4F color;
};

