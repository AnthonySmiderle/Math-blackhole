
#include "Rectangle.h"

C_Rectangle::C_Rectangle(Scene* parentScene, Vec2 position, Vec2 offset, float width, float height, Color4F color)
{
	// Set Data
	this->position = position;
	this->width = width;
	this->height = height;
	this->color = color;

	// Create Node
	drawNode = DrawNode::create();

	// Set to Circle
	drawNode->drawSolidRect(Vec2(-width*0.5f + offset.x, -height*0.5f + offset.y), Vec2(width*0.5f + offset.x, height*0.5f + offset.y), color);

	setPosition(position);

	// Add self to scecne
	parentScene->addChild(drawNode);
}

C_Rectangle::~C_Rectangle()
{
	drawNode = nullptr;
}

void C_Rectangle::setPosition(Vec2 position)
{
	this->position = position;

	if (drawNode != nullptr)
	{
		drawNode->setPosition(position);
	}
}

void C_Rectangle::setRotation(float angle)
{
	if (drawNode != nullptr)
	{
		drawNode->setRotation(angle);
	}
}
