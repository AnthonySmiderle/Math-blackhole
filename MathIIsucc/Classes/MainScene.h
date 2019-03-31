#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "cocos2d.h"
#include "PhysicsCircle.h"
using namespace cocos2d;

#define NUM_PLANETS 3

class MainScene : public cocos2d::Scene
{
public:
	//--- Required Cocos2D Functions ---//
    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(MainScene);

	//--- Init Functions ---//
	void initCocosReferences();
	void initPrivateVariables();
	void initScene();

	//--- Update Functions ---//
	void updatePlanets(float _dt);

	//--- Methods ---//
	void applyGravityToPlanets();

private:
	//--- Cocos Engine References ---//
	Director* director;

	//--- Static Constants ---//
	static float degToRad;
	static float radToDeg;
	static float gravity;

	//--- Private Variables ---//
	Vec2 sunPosition;
	float sunRadius;
	float M;
	float G;

	//--- Scene Object References ---//
	PhysicsCircle sun;
	PhysicsCircle planets[NUM_PLANETS];
};

#endif
