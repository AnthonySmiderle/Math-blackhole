#pragma once

#include <vector>

#include "cocos2d.h"
using namespace cocos2d;

class C_Lines
{
public:
	C_Lines(Scene* parentScene, std::vector<Vec2> points, float LineWidth, Color4F color);
	~C_Lines();

	void setOffset(Vec2 position);
	void rotateAll(float degrees);

private:
	DrawNode* drawNode = nullptr;

	Vec2 offset;
	std::vector<Vec2> points;
};

