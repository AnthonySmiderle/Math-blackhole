
#include "Circle.h"

C_Circle::C_Circle(Scene* parentScene, Vec2 position, Vec2 offset, float radius, float mass,Color4F color)
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

void C_Circle::update(float dt)
{
	force = Vec2(0.0f, mass*-98.0f);
	acceleration = force / mass;
	velocity += acceleration * dt;

	setPosition(position  +(velocity*dt));
}

Vec2 C_Circle::getVelocity() const
{
	return velocity;
}

Vec2 C_Circle::getAccel() const
{
	return acceleration;
}

Vec2 C_Circle::getForce() const
{
	return force;
}

float C_Circle::getMass() const
{
	return mass;
}

void C_Circle::setVelocity(Vec2 v)
{
	velocity = v;
}

void C_Circle::setAccel(Vec2 a)
{
	acceleration = a;
}

void C_Circle::setForce(Vec2 f)
{
	force = f;
}

void C_Circle::setMass(float m)
{
	mass = m;
}
