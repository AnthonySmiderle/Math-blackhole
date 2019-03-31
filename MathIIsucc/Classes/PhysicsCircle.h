#ifndef ELLIPSE_H
#define ELLPISE_H

#include "cocos2d.h"
using namespace cocos2d;

class PhysicsCircle
{
public:
	//--- Constructors and Destructor ---//
	PhysicsCircle();
	PhysicsCircle(Scene* _scene, float _x, float _y, float _radius, float _mass, Color4F _color);
	PhysicsCircle(Scene* _scene, Vec2 _pos, float _radius, float _mass, Color4F _color);
	~PhysicsCircle();



	//--- Setters and Getters ---//
	//Radius
	void setRadius(float _radius);
	float getRadius() const;


	//Mass
	void setMass(float _mass);
	float getMass() const;


	//Pos
	void setPosition(Vec2 _pos);
	Vec2 getPosition() const;


	//Color
	void setColor(Color4F _color);
	Color4F getColor() const;


	//Velocity
	void setVelocity(Vec2 _vel);
	Vec2 getVelocity() const;


	//Force
	void setForce(Vec2 _force);
	Vec2 getForce() const;


	//Acceleration
	void setAcceleration(Vec2 _accel);
	Vec2 getAcceleration() const;



	//--- Methods ---//
	void update(float _dt);



private:
	//--- Private Variables ---//
	Scene* attachedScene;
	DrawNode* drawNode;
	float radius;
	float mass;
	Vec2 position;
	Color4F color;
	Vec2 velocity;
	Vec2 force;
	Vec2 acceleration;



	//--- Utility Functions ---//
	void initDrawNode();
};

#endif
