
#include "Circle.h"

Blackhole::Blackhole(Scene* parentScene, Vec2 position, Vec2 offset, float radius, float mass,Color4F color)
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

Blackhole::~Blackhole()
{
	parentScene->removeChild(drawNode);

	drawNode = nullptr;
}

void Blackhole::setPosition(Vec2 position)
{
	this->position = position;

	if (drawNode != nullptr)
	{
		drawNode->setPosition(position);
	}
}

void Blackhole::update(float dt)
{
	force = Vec2(0.0f, mass*-98.0f);
	acceleration = force / mass;
	velocity += acceleration * dt;

	setPosition(position  +(velocity*dt));
}

Vec2 Blackhole::getVelocity() const
{
	return velocity;
}

Vec2 Blackhole::getAccel() const
{
	return acceleration;
}

Vec2 Blackhole::getForce() const
{
	return force;
}

float Blackhole::getMass() const
{
	return mass;
}

void Blackhole::setVelocity(Vec2 v)
{
	velocity = v;
}

void Blackhole::setAccel(Vec2 a)
{
	acceleration = a;
}

void Blackhole::setForce(Vec2 f)
{
	force = f;
}

void Blackhole::setMass(float m)
{
	mass = m;
}

bool Blackhole::checkCollision(const Blackhole & other)
{
	///code from gdw
	float distance = sqrt((this->position.x - other.position.x)*(this->position.x - other.position.x) +
		(this->position.y - other.position.y)*(this->position.y - other.position.y));

	if (distance <= (this->radius + other.radius))
		return true;

	return false;
}
