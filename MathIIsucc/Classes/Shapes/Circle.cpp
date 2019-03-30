
#include "Circle.h"

S_Dot::S_Dot(Scene* parentScene, Vec2 position, Vec2 offset, float radius, float mass,Color4F color)
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

	if (drawNode != nullptr)
	{
		drawNode->setPosition(position);
	}
}

void S_Dot::update(float dt)
{
	//force = Vec2(0.0f, mass*-98.0f);
	acceleration = force / mass;
	velocity += acceleration * dt;

	setPosition(position  +(velocity*dt));
}

Vec2 S_Dot::getVelocity() const
{
	return velocity;
}

Vec2 S_Dot::getAccel() const
{
	return acceleration;
}

Vec2 S_Dot::getForce() const
{
	return force;
}

float S_Dot::getMass() const
{
	return mass;
}

void S_Dot::setVelocity(Vec2 v)
{
	velocity = v;
}

void S_Dot::setAccel(Vec2 a)
{
	acceleration = a;
}

void S_Dot::setForce(Vec2 f)
{
	force = f;
}

void S_Dot::setMass(float m)
{
	mass = m;
}

bool S_Dot::checkCollision(const S_Dot & other)
{
	///code from gdw
	float distance = sqrt((this->position.x - other.position.x)*(this->position.x - other.position.x) +
		(this->position.y - other.position.y)*(this->position.y - other.position.y));

	if (distance <= (this->radius + other.radius))
		return true;

	return false;
}
