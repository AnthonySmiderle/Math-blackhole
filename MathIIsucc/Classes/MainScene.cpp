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
	T1 = new BasecodeTriangle(this, Vec2(250, 100), 30.0f);
	T1->setPosition(cocos2d::Vec2(700, 30));

	srand(time(0));
	spawnBlackholes();
	spawnParticles();

	//text1 = new BasecodeText(this, std::to_string(levelNumber), "fonts/arial.ttf", 15.0f, Vec2(0, 300));
	levelLabel = cocos2d::Label::create(std::to_string(levelNumber), "fonts/arial.ttf", 50);
	levelLabel->setPosition(cocos2d::Vec2(200, 900));
	levelLabel->setColor(cocos2d::Color3B::BLACK);
	levelLabel->setVisible(true);

	gameoverLabel = cocos2d::Label::create("Game Over", "fonts/arial.ttf", 30);
	gameoverLabel->setPosition(cocos2d::Vec2(300, 500));
	gameoverLabel->setVisible(false);
	gameoverLabel->setColor(cocos2d::Color3B::BLACK);

	this->addChild(levelLabel);
	this->addChild(gameoverLabel);
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
	for (unsigned i = 0; i < blackholes.size(); ++i) {
		delete blackholes[i];
		blackholes.erase(blackholes.begin() + i);
		i--;
	}
	for (int i = 0; i < levelNumber; ++i) {
		auto r = 10 + rand() % 50;
		auto mass = ((c*c) / 2 * G) * r;
		blackholes.push_back(new S_Dot(this, cocos2d::Vec2(rand() % (int)windowSize.x, rand() % (int)windowSize.y), cocos2d::Vec2(0, 0), r, mass, cocos2d::Color4F::BLACK));
	}
	checkSamePosition(blackholes);
}

void MainScene::checkPlayerInput(float dt)
{
	static bool one = false, two = false, three = false;
	if (p1Sticks[0].x < -0.3f || INPUTS->getKey(KeyCode::KEY_LEFT_ARROW))
		T1->addForce(cocos2d::Vec2(-15, 0), dt);

	else if (p1Sticks[0].x > 0.3f || INPUTS->getKey(KeyCode::KEY_RIGHT_ARROW))
		T1->addForce(cocos2d::Vec2(15, 0), dt);

	if (p1Sticks[0].y < -0.3f || INPUTS->getKey(KeyCode::KEY_DOWN_ARROW))
		T1->addForce(cocos2d::Vec2(0, -15), dt);

	else if (p1Sticks[0].y > 0.3f || INPUTS->getKey(KeyCode::KEY_UP_ARROW))
		T1->addForce(cocos2d::Vec2(0, 15), dt);


}

void MainScene::spawnParticles()
{
	for (unsigned i = 0; i < particles.size(); ++i) {
		delete particles[i];
		particles.erase(particles.begin() + i);
		i--;
	}
	for (int i = 0; i < 100; ++i) {
		auto r = 5 + rand() % 10;
		auto mass = ((c*c) / 2 * G) * r;
		particles.push_back(new S_Dot(this, cocos2d::Vec2(rand() % (int)windowSize.x, rand() % (int)windowSize.y), cocos2d::Vec2(0, 0), r, mass, cocos2d::Color4F(0.5f + rand() % 2, 0.5f + rand() % 2, 0.5f + rand() % 2, 1)));
	}
}

void MainScene::gravitate(S_Dot & s, S_Dot & t)
{
	auto M = s.getMass() > t.getMass() ? s.getMass() : t.getMass();
	auto m = s.getMass() > t.getMass() ? t.getMass() : s.getMass();
	auto R = s.getMass() > t.getMass() ? t.getPosition() - s.getPosition() : s.getPosition() - t.getPosition();
	auto r = sqrt(R.x*R.x + R.y*R.y);


	///<gravitation woooooooooooooo>
	if (s.getMass() > t.getMass())
		t.setForce(((-(G*M*m) / (r * r*r)) * R * 300));
	else if (s.getMass() < t.getMass())
		s.setForce(((-(G*M*m) / (r * r*r)) * R * 300));

}

void MainScene::gravitate(S_Dot & s, BasecodeTriangle & t, float dt)
{
	auto M = s.getMass() > t.getMass() ? s.getMass() : t.getMass();
	auto m = s.getMass() > t.getMass() ? t.getMass() : s.getMass();
	auto R = t.getPosition() - s.getPosition();
	auto r = sqrt(R.x*R.x + R.y*R.y);


	///<gravitation woooooooooooooo>
	t.addForce(((-(G*M*m) / (r * r*r)) * R) / 30, dt);
}

void MainScene::update(float dt)
{
	manager.update();
	p1->updateSticks(p1Sticks);

	if (blackholes.size() != levelNumber) {
		spawnBlackholes();
		spawnParticles();
	}

	if (particles.size() < 100) {
		auto r = 5 + rand() % 10;
		auto mass = ((c*c) / 2 * G) * r;
		particles.push_back(new S_Dot(this, cocos2d::Vec2(rand() % (int)windowSize.x, rand() % (int)windowSize.y), cocos2d::Vec2(0, 0), r, mass, cocos2d::Color4F(0.5f + rand() % 2, 0.5f + rand() % 2, 0.5f + rand() % 2, 1)));
	}
	checkPlayerInput(dt);

	for (int i = 0; i < blackholes.size(); ++i) {
		for (int j = 0; j < particles.size(); ++j) {
			gravitate(*blackholes[i], *particles[j]);
			particles[j]->update(dt);
		}
		gravitate(*blackholes[i], *T1, dt);
		blackholes[i]->update(dt);

	}

	T1->update(dt);

	if (T1->getPosition().y >= 1100) {
		T1->setPosition(cocos2d::Vec2(700, 30));
		levelNumber++;
		levelLabel->setString(std::to_string(levelNumber));
	}

	for (unsigned i = 0; i < blackholes.size(); ++i) {
		if (blackholes[i]->checkCollision(*T1->getBox()))
		{
			T1->setPosition(cocos2d::Vec2(700, 30));
			T1->setForce(cocos2d::Vec2(0, 0));
			T1->lives--;
			if (T1->lives == 0) {
				gameoverLabel->setVisible(true);
			}
		}
		for (unsigned j = 0; j < particles.size(); ++j) {
			if (blackholes[i]->checkCollision(*particles[j])) {
				delete particles[j];
				particles.erase(particles.begin() + j);
				j--;
			}
		}
	}

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