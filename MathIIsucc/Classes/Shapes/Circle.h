#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class C_Circle
{
public:
	C_Circle(Scene* parentScene, Vec2 position, Vec2 offset, float radius, Color4F color);
	~C_Circle();

	void setPosition(Vec2 position);

private:
	Scene* parentScene = nullptr;
	DrawNode* drawNode = nullptr;

	Vec2 position;
	Vec2 offset;
	float radius;
	Color4F color;
};

