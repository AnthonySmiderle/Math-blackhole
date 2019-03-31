#pragma once
#include <iostream>
#include "cocos2d.h"
#include "Circle.h"
using namespace cocos2d;

class BasecodeTriangle
{
public:
	BasecodeTriangle(Scene* parentScene, Vec2 Position, float size, Color4F color = Color4F::RED)
	{
		this->Position = Position;

		// Create Node
		drawNode = DrawNode::create();

		hitbox = new S_Dot(parentScene, Position, cocos2d::Vec2(0, 0), 5, 1, cocos2d::Color4F::WHITE);
		
		// Add Triangle
		drawNode->drawTriangle(
			Vec2(-1, -1).getNormalized() * (size * 0.5f),
			Vec2(+1, -1).getNormalized() * (size * 0.5f),
			Vec2(0, 1).getNormalized() * (size * 0.5f),
			color
		);
		mass = 10.0f;



		// Set Position
		setPosition(Position);

		// Add self to scecne
		parentScene->addChild(drawNode);
	}
	
	void setPosition(Vec2 p)
	{
		Position = p;
		drawNode->setPosition(p);
	}
	Vec2 getPosition()
	{
		return Position;
	}
	float getMass() const {
		return mass;
	}
	//code from our gdw game
	void setForce(const cocos2d::Vec2& v) {
		velocity = v / 1000;
	}
	void addForce(const cocos2d::Vec2& v,float dt) {
		int maxVelocity = 4;
		int minVelocity = -4;

		velocity += v*dt;//acceleration 

		if (velocity.x >= maxVelocity)
			velocity.x = maxVelocity;
		else if (velocity.x <= minVelocity)
			velocity.x = minVelocity;
		if (velocity.y >= maxVelocity)
			velocity.y = maxVelocity;
		else if (velocity.y <= minVelocity)
			velocity.y = minVelocity;
	}


	void update(float dt) {

		Position += velocity;
		drawNode->setPosition(Position);
		hitbox->setPosition(Position);
		///std::cout << Position.x<<" "<<Position.y<<"\n";
	}
	
	S_Dot* getBox() const {
		return hitbox;
	}

	unsigned lives = 3;
private:
	DrawNode* drawNode = nullptr;

	S_Dot* hitbox;
	float mass;
	cocos2d::Vec2 velocity;
	Vec2 Position;
};