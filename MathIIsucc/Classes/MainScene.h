#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "cocos2d.h"
using namespace cocos2d;

#include "Classes/Shapes/Circle.h"
#include "Classes/Shapes/Lines.h"
#include "Classes/Shapes/Rectangle.h"
#include "Classes/Shapes/Triangle.h"
#include "Classes/Shapes/Text.h"

// If you want to change the size of your window,
// look for this:
// DISPLAY->init(1024, 512, "Assignment 2", false, 1.0f);
// in AppDelegate.cpp

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


private:
	//--- Cocos Engine References ---//
	Director* director;

	//--- Static Constants ---//
	const static float degToRad;
	const static float radToDeg;

	//--- Private Variables ---//
	Label* label_Angle;

	//--- Scene Object References ---//
	C_Triangle* T1;
	C_Circle* C1;
	C_Text* text1;
};

#endif
