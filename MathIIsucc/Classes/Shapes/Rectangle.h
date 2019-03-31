#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class C_Rectangle
{
public:
	C_Rectangle(Scene* parentScene, Vec2 position, Vec2 offset, float width, float height, Color4F color);
	~C_Rectangle();

	void setPosition(Vec2 position);
	void setRotation(float angle);

	float getLeftX()
	{
		return position.x - width * 0.5f;
	}
	float getRightX()
	{
		return position.x + width * 0.5f;
	}
	float getTopY()
	{
		return position.y + height * 0.5f;
	}
	float getBottomY()
	{
		return position.y - height * 0.5f;
	}

private:
	DrawNode* drawNode = nullptr;

	Vec2 position;
	float width;
	float height;
	Color4F color;
};

