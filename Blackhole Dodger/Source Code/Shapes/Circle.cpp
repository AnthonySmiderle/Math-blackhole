
#include "Circle.h"

S_Dot::S_Dot(Scene* parentScene, Vec2 position, Vec2 offset, float radius, float mass, Color4F color)
{
	this->parentScene = parentScene;

	// Set Data
	this->position = position;
	this->offset = offset;
	this->radius = radius;
	this->color = color;
	this->mass = mass;

	velocity = Vec2(0.0f, 0.0f);
	acceleration = Vec2(0.0f, 0.0f);
	force = Vec2(0.0f, 0.0f);

	// Create Node
	drawNode = DrawNode::create();

	setPosition(position);

	// Set to Circle
	drawNode->drawDot(offset, radius, color);

	// Add self to scecne
	parentScene->addChild(drawNode);
}

S_Dot::~S_Dot()
{
	parentScene->removeChild(drawNode);
	drawNode = nullptr;
}

void S_Dot::setPosition(Vec2 position)
{
	this->position = position;
	drawNode->setPosition(position);
}

void S_Dot::update(float dt)
{
	acceleration = (force / mass);
	velocity += acceleration * dt;

	setPosition(position + (velocity*dt));
}


float S_Dot::getMass() const
{
	return mass;
}

void S_Dot::setForce(Vec2 f)
{
	force = f;
}

bool S_Dot::checkCollision(const S_Dot & other)
{
	///code from gdw
	//magnitude of the distance vector
	float distance = sqrt((this->position.x - other.position.x)*(this->position.x - other.position.x) +
		(this->position.y - other.position.y)*(this->position.y - other.position.y));

	//if they are touching or intersecting
	if (distance <= (this->radius + other.radius))
		return true;

	return false;
}
