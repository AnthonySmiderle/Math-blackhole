#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class C_Triangle
{
public:
	C_Triangle(Scene* parentScene, Vec2 Position, float size, Color4F color = Color4F::RED)
	{
		this->Position = Position;

		// Create Node
		drawNode = DrawNode::create();

		// Add Triangle
		drawNode->drawTriangle(
			Vec2(-1, -1).getNormalized() * (size * 0.5f),
			Vec2(+1, -1).getNormalized() * (size * 0.5f),
			Vec2(0, 1).getNormalized() * (size * 0.5f),
			color
		);

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


private:
	DrawNode* drawNode = nullptr;

	Vec2 Position;
};