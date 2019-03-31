
#include "Circle.h"

C_Circle::C_Circle(Scene* parentScene, Vec2 position, Vec2 offset, float radius, Color4F color)
{
	this->parentScene = parentScene;

	// Set Data
	this->position = position;
	this->offset = offset;
	this->radius = radius;
	this->color = color;

	// Create Node
	drawNode = DrawNode::create();
	
	setPosition(position);

	// Set to Circle
	drawNode->drawDot(offset, radius, color);

	// Add self to scecne
	parentScene->addChild(drawNode);
}

C_Circle::~C_Circle()
{
	parentScene->removeChild(drawNode);

	drawNode = nullptr;
}

void C_Circle::setPosition(Vec2 position)
{
	this->position = position;

	if (drawNode != nullptr)
	{
		drawNode->setPosition(position);
	}
}
