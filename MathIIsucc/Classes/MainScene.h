#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "cocos2d.h"
using namespace cocos2d;

#include "Classes/Shapes/Circle.h"
#include "Classes/Shapes/Lines.h"
#include "Classes/Shapes/Rectangle.h"
#include "Classes/Shapes/Triangle.h"
#include "Classes/Shapes/Text.h"
#include <vector>

#define c 200
#define G 1

class MainScene : public cocos2d::Scene
{
public:
	//--- Required Cocos2D Functions ---//
    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(MainScene);

	//--- Init Functions ---//
	void initSceneObjects();


	//functions that do game specific things
	void spawnBlackholes();
	void spawnParticles();
	void gravitate(S_Dot & s, S_Dot & t);
	void gravitate(S_Dot& s, BasecodeTriangle& t,float dt);
	void checkSamePosition(std::vector<S_Dot*>& blackholes);
	void checkPlayerInput(float dt);

private:
	unsigned levelNumber = 1; 
	Vec2 windowSize;


	//--- Cocos Engine References ---//
	Director* director;

	//--- Static Constants ---//
	const static float degToRad;
	const static float radToDeg;

	//--- Private Variables ---//
	Label* label_Angle;

	//--- Scene Object References ---//
	BasecodeTriangle* T1;
	std::vector<S_Dot*> blackholes;
	std::vector<S_Dot*> particles;

	BasecodeText* text1;

	cocos2d::Label* levelLabel;
	cocos2d::Label* gameoverLabel;

	float gameoverTimer = 0.0f;
	bool hasEnded = false;
};

#endif


