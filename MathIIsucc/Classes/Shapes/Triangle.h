#pragma once
#include <iostream>
#include "cocos2d.h"
#include "Circle.h"
using namespace cocos2d;

class BasecodeTriangle
{
public:
	BasecodeTriangle(Scene* parentScene, Vec2 Position, float size, Color4F color = Color4F::RED);
	
	void setPosition(Vec2 p);
	Vec2 getPosition();
	float getMass() const;

	//code from our gdw game
	void setForce(const cocos2d::Vec2& v);
	void addForce(const cocos2d::Vec2& v, float dt);


	void update(float dt);
	
	S_Dot* getBox() const;

	unsigned lives = 3;//really no reason for this to have a getter / setter
private:
	DrawNode* drawNode = nullptr;

	S_Dot* hitbox;
	float mass;
	cocos2d::Vec2 velocity;
	Vec2 Position;
};