#include "MainScene.h"
#include "DisplayHandler.h"
#include "InputHandler.h"
#include <iostream>
#include <stdio.h>



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
	windowSize = DISPLAY->getWindowSizeAsVec2();
	T1 = new BasecodeTriangle(this, Vec2(100, 100), 30.0f);
	C1 = new S_Dot(this, Vec2(200, 100), Vec2(0, 0), 30.0f, 10.0f, Color4F::BLACK);

	srand(time(0));
	spawnBlackholes();

	text1 = new BasecodeText(this, "1234567890", "fonts/arial.ttf", 15.0f, Vec2(0, 300));
}

void MainScene::checkSamePosition(std::vector<S_Dot*>& blackholes)
{
	for (unsigned int i = 0; i < blackholes.size(); i++) {
		for (unsigned int j = 0; j < blackholes.size(); j++) {
			if (i == j)
				continue;
			if (blackholes[i]->checkCollision(*blackholes[j])) {
				blackholes[i]->setPosition(
					cocos2d::Vec2(100 + (rand() % 300),
						blackholes[i]->getPosition().y + 50));
				checkSamePosition(blackholes);
			}

		}

	}
}

void MainScene::spawnBlackholes()
{
	for (int i = 0; i < numBlackholes; ++i) {
		auto r = 20 + rand() % 40;
		auto mass = ((c*c) / 2 * G) * r;
		blackholes.push_back(new S_Dot(this, cocos2d::Vec2(rand() % (int)windowSize.x, rand() % (int)windowSize.y), cocos2d::Vec2(0, 0), r, mass, cocos2d::Color4F::BLACK));
	}
	checkSamePosition(blackholes);
}

void MainScene::checkPlayerInput(float dt)
{

	if (p1Sticks[0].x < -0.3f || INPUTS->getKey(KeyCode::KEY_A))
		T1->addForce(cocos2d::Vec2(-10, 0), dt);

	else if (p1Sticks[0].x > 0.3f || INPUTS->getKey(KeyCode::KEY_D))
		T1->addForce(cocos2d::Vec2(10, 0), dt);

	if (p1Sticks[0].y < -0.3f || INPUTS->getKey(KeyCode::KEY_S))
		T1->addForce(cocos2d::Vec2(0, -10), dt);

	else if (p1Sticks[0].y > 0.3f || INPUTS->getKey(KeyCode::KEY_W))
		T1->addForce(cocos2d::Vec2(0, 10), dt);
}

void MainScene::gravitate(S_Dot & s,S_Dot & t)
{
	auto M = s.getMass();
	auto m = t.getMass();
	auto R = s.getPosition() - t.getPosition();
	auto r = sqrt(R.x*R.x + R.y*R.y);

	cocos2d::Vec2 F = (-(G*M*m) / r) * R;
	s.setForce(F);
	s.setForce(F);
}

void MainScene::update(float dt)
{
	manager.update();
	p1->updateSticks(p1Sticks);

	if (blackholes.size() != numBlackholes) 
		spawnBlackholes();

	checkPlayerInput(dt);

	T1->update(dt);
	

	///Vec2 Mpos = INPUTS->getMousePosition();
	///
	///float distX = Mpos.x - C1->getPosition().x;
	///float distY = Mpos.y - C1->getPosition().y;
	///
	///float distance = sqrt((distX*distX) + (distY*distY));
	///
	///if (INPUTS->getMouseButton(MouseButton::BUTTON_LEFT)) {
	///	if (distance <= C1->getRadius())
	///		mouseCheck = true;
	///
	///}
	///else
	///	mouseCheck = false;
	///if (mouseCheck)
	///	C1->setPosition(Mpos);
	///
	///if (C1->getPosition().y > C1->getRadius())
	///	C1->update(dt);
	///else
	///	C1->setVelocity(Vec2(0.0f, 0.0f));
	///text1->setText(std::to_string(C1->getVelocity().x) + ", " + std::to_string(C1->getVelocity().y));
}