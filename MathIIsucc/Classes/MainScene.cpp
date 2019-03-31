#include "MainScene.h"
#include "DisplayHandler.h"
#include "InputHandler.h"
#include <iostream>

//--- Static Constants ---//
const float MainScene::degToRad = 3.14159f / 180.0f;
const float MainScene::radToDeg = 180.0f / 3.14159f;


//--- Required Cocos2D Functions ---//
cocos2d::Scene* MainScene::createScene()
{
	//Create a scene without physics (we're implementing our own!)
	Scene* scene = Scene::create();

	//Create the main layer that is attached to the scene
	MainScene* layer = MainScene::create();

	//Add the layer to the scene
	scene->addChild(layer);

	//Return the newly built scene
	return scene;
}

bool MainScene::init()
{
	//Ensure the parent's class init'd properly. If it didn't, terminate the program
	if (!Scene::init())
		return false;

	//Store the director singleton for easy access
	director = Director::getInstance();

	//Make the background of our scene white instead of the default black
	director->setClearColor(Color4F(255, 255, 255, 255));

	//Schedule the use of the update function so the function actually gets called
	this->scheduleUpdate();

	// Custom init function
	initSceneObjects();
	
	//Let Cocos know that the init function was successful
	return true;
}

void MainScene::initSceneObjects()
{
	//Store the window dimensions so we don't have to call the same function a bunch of times
	Vec2 windowSize = DISPLAY->getWindowSizeAsVec2();

	T1 = new C_Triangle(this, Vec2(100, 100), 30.0f);
	C1 = new C_Circle(this, Vec2(200, 100), Vec2(0, 0), 30.0f, Color4F::BLACK);

	text1 = new C_Text(this, "1234567890", "fonts/arial.ttf", 15.0f, Vec2(0, 300));
}

void MainScene::update(float deltaTime)
{

}