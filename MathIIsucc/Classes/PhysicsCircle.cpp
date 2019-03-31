#include "PhysicsCircle.h"

//--- Constructors and Destructors ---//
PhysicsCircle::PhysicsCircle()
{
	//Init all of the private variables
	attachedScene = nullptr;
	drawNode = nullptr;
	radius = 0.0f;
	mass = 0.0f;
	position = Vec2(0.0f, 0.0f);
	color = Color4F(1.0f, 1.0f, 1.0f, 1.0f);
	velocity = Vec2(0.0f, 0.0f);
	force = Vec2(0.0f, 0.0f);
	acceleration = Vec2(0.0f, 0.0f);
}

PhysicsCircle::PhysicsCircle(Scene* _scene, float _x, float _y, float _radius, float _mass, Color4F _color)
{
	//Set the given variables
	attachedScene = _scene;
	position = Vec2(_x, _y);
	radius = _radius;
	mass = _mass;
	color = _color;

	//Init the remaining variables
	velocity = Vec2(0.0f, 0.0f);
	force = Vec2(0.0f, 0.0f);
	acceleration = Vec2(0.0f, 0.0f);

	//Init the draw node
	initDrawNode();
}

PhysicsCircle::PhysicsCircle(Scene* _scene, Vec2 _pos, float _radius, float _mass, Color4F _color)
{
	//Set the given variables
	attachedScene = _scene;
	position = _pos;
	radius = _radius;
	mass = _mass;
	color = _color;

	//Init the remaining variables
	velocity = Vec2(0.0f, 0.0f);
	force = Vec2(0.0f, 0.0f);
	acceleration = Vec2(0.0f, 0.0f);

	//Init the draw node
	initDrawNode();
}

PhysicsCircle::~PhysicsCircle()
{
	//Clean up the pointers for safety
	attachedScene = nullptr;
	drawNode = nullptr;
}



//--- Setters and Getters ---//
//Radius
void PhysicsCircle::setRadius(float _radius) {
	radius = _radius;
}

float PhysicsCircle::getRadius() const {
	return radius;
}


//Mass
void PhysicsCircle::setMass(float _mass) {
	mass = _mass;
}

float PhysicsCircle::getMass() const {
	return mass;
}


//Pos
void PhysicsCircle::setPosition(Vec2 _pos) {
	position = _pos;
}

Vec2 PhysicsCircle::getPosition() const {
	return position;
}


//Color
void PhysicsCircle::setColor(Color4F _color) {
	color = _color;
}

Color4F PhysicsCircle::getColor() const {
	return color;
}


//Velocity
void PhysicsCircle::setVelocity(Vec2 _vel) {
	velocity = _vel;
}

Vec2 PhysicsCircle::getVelocity() const {
	return velocity;
}


//Force
void PhysicsCircle::setForce(Vec2 _force) {
	force = _force;
}

Vec2 PhysicsCircle::getForce() const {
	return force;
}


//Acceleration
void PhysicsCircle::setAcceleration(Vec2 _accel) {
	acceleration = _accel;
}

Vec2 PhysicsCircle::getAcceleration() const {
	return acceleration;
}



//--- Methods ---//
void PhysicsCircle::update(float _dt)
{
	//Integrate force into acceleration
	acceleration = force * (1.0f / mass);

	//Integrate acceleration into velocity
	velocity += (acceleration * _dt);

	//Integrate velocity into position
	position += (velocity * _dt);

	//Update the position of the draw node to sync the visuals
	drawNode->setPosition(position);
}



//--- Utility Functions ---//
void PhysicsCircle::initDrawNode()
{
	//Create the draw node and put it into the scene
	drawNode = DrawNode::create();
	drawNode->setPosition(position);
	drawNode->drawDot(Vec2(0.0f, 0.0f), radius, color);
	attachedScene->addChild(drawNode);
}