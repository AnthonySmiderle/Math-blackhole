
#include "Triangle.h"

BasecodeTriangle::BasecodeTriangle(Scene * parentScene, Vec2 Position, float size, Color4F color)
{
	this->Position = Position;

	// Create Node
	drawNode = DrawNode::create();

	//create the hitbox
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

void BasecodeTriangle::setPosition(Vec2 p)
{
	Position = p;
	drawNode->setPosition(p);
}

Vec2 BasecodeTriangle::getPosition()
{
	return Position;
}

float BasecodeTriangle::getMass() const
{
	return mass;
}

void BasecodeTriangle::setForce(const cocos2d::Vec2 & v)
{
	velocity = v;
}

void BasecodeTriangle::addForce(const cocos2d::Vec2 & v, float dt)
{
	//this is code from our gdw game, the way we do acceleration boils down to the same thing that the base code was doing
	int maxVelocity = 4;
	int minVelocity = -4;

	velocity += v * dt;//acceleration 

	//make sure that the player doesn't zoom too fast
	if (velocity.x >= maxVelocity)
		velocity.x = maxVelocity;

	else if (velocity.x <= minVelocity)
		velocity.x = minVelocity;

	if (velocity.y >= maxVelocity)
		velocity.y = maxVelocity;

	else if (velocity.y <= minVelocity)
		velocity.y = minVelocity;
}

void BasecodeTriangle::update(float dt)
{
	Position += velocity;
	drawNode->setPosition(Position);
	hitbox->setPosition(Position);
}

S_Dot * BasecodeTriangle::getBox() const
{
	return hitbox;
}
