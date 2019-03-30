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

	p1 = manager.getController(0);
	manager.update();

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
	C1 = new C_Circle(this, Vec2(200, 100), Vec2(0, 0), 30.0f, 10.0f, Color4F::BLACK);

	text1 = new C_Text(this, "1234567890", "fonts/arial.ttf", 15.0f, Vec2(0, 300));
}

void MainScene::update(float deltaTime)
{
	manager.update();
	p1->updateSticks(p1Sticks);

	if (p1Sticks[0].x < -0.3f || INPUTS->getKey(KeyCode::KEY_A))
		T1->setPosition(T1->getPosition() - Vec2(10.0f, 0.0f));
	else if (p1Sticks[0].x > 0.3f || INPUTS->getKey(KeyCode::KEY_D))
		T1->setPosition(T1->getPosition() + Vec2(10.0f, 0.0f));
	if (p1Sticks[0].y < -0.3f || INPUTS->getKey(KeyCode::KEY_S))
		T1->setPosition(T1->getPosition() - Vec2(0.0f, 10.0f));
	else if (p1Sticks[0].y > 0.3f || INPUTS->getKey(KeyCode::KEY_W))
		T1->setPosition(T1->getPosition() + Vec2(0.0f, 10.0f));

	Vec2 Mpos = INPUTS->getMousePosition();

	float distX = Mpos.x - C1->getPosition().x;
	float distY = Mpos.y - C1->getPosition().y;

	float distance = sqrt((distX*distX) + (distY*distY));

	if (INPUTS->getMouseButton(MouseButton::BUTTON_LEFT)) {
		if (distance <= C1->getRadius()) 
			mouseCheck = true;
		
	}
		else
			mouseCheck = false;
	if(mouseCheck)
	C1->setPosition(Mpos);

	if (C1->getPosition().y > C1->getRadius())
		C1->update(deltaTime);
	else
		C1->setVelocity(Vec2(0.0f, 0.0f));
	text1->setText(std::to_string(C1->getVelocity().x) + ", " + std::to_string(C1->getVelocity().y));
}