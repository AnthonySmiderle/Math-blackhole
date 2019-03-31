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
	//make the player
	T1 = new BasecodeTriangle(this, Vec2(250, 100), 30.0f);
	T1->setPosition(cocos2d::Vec2(700, 30));

	//spawn stuff
	srand(time(0));
	spawnBlackholes();
	spawnParticles();

	//create the level label
	levelLabel = cocos2d::Label::create(std::to_string(levelNumber), "fonts/arial.ttf", 50);
	levelLabel->setPosition(cocos2d::Vec2(200, 900));
	levelLabel->setColor(cocos2d::Color3B::BLACK);
	levelLabel->setVisible(true);

	//create the gameover label
	gameoverLabel = cocos2d::Label::create("Game Over", "fonts/arial.ttf", 30);
	gameoverLabel->setPosition(cocos2d::Vec2(300, 500));
	gameoverLabel->setVisible(false);
	gameoverLabel->setColor(cocos2d::Color3B::BLACK);

	this->addChild(levelLabel);
	this->addChild(gameoverLabel);
}

void MainScene::checkSamePosition(std::vector<S_Dot*>& blackholes)
{
	//check to see if the blackholes are spawned in the same position
	for (unsigned int i = 0; i < blackholes.size(); i++) {
		for (unsigned int j = 0; j < blackholes.size(); j++) {
			if (i == j)
				continue;
			if (blackholes[i]->checkCollision(*blackholes[j])) {
				//change the position of the blackhole
				blackholes[i]->setPosition(cocos2d::Vec2(100 + (rand() % 300), blackholes[i]->getPosition().y + 50));
				//do the whole process again until nothing is touching
				checkSamePosition(blackholes);
			}

		}

	}
}

void MainScene::spawnBlackholes()
{
	//delete all the previous blackholes
	for (unsigned i = 0; i < blackholes.size(); ++i) {
		delete blackholes[i];
		blackholes.erase(blackholes.begin() + i);
		i--;
	}

	//spawn blackholes, up to the number of the current level
	for (int i = 0; i < levelNumber; ++i) {
		auto r = 11 + rand() % 50;
		auto mass = ((c*c) / (2 * G)) * r;
		blackholes.push_back(new S_Dot(this, cocos2d::Vec2(rand() % (int)windowSize.x, rand() % (int)windowSize.y), cocos2d::Vec2(0, 0), r, mass, cocos2d::Color4F::BLACK));
	}
	checkSamePosition(blackholes);
}

void MainScene::checkPlayerInput(float dt)
{
	//check to see if the player is pressing a certain key, then push them in that direction
	if (INPUTS->getKey(KeyCode::KEY_LEFT_ARROW))
		T1->addForce(cocos2d::Vec2(-15, 0), dt);

	else if (INPUTS->getKey(KeyCode::KEY_RIGHT_ARROW))
		T1->addForce(cocos2d::Vec2(15, 0), dt);

	if (INPUTS->getKey(KeyCode::KEY_DOWN_ARROW))
		T1->addForce(cocos2d::Vec2(0, -15), dt);

	else if (INPUTS->getKey(KeyCode::KEY_UP_ARROW))
		T1->addForce(cocos2d::Vec2(0, 15), dt);

}

void MainScene::spawnParticles()
{
	//this function is the same as spawn blackholes, just spawns smaller dots that arent blackholes
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
	//set our givens to their appropriate values
	auto M = s.getMass() > t.getMass() ? s.getMass() : t.getMass();
	auto m = s.getMass() > t.getMass() ? t.getMass() : s.getMass();
	auto R = s.getMass() > t.getMass() ? t.getPosition() - s.getPosition() : s.getPosition() - t.getPosition();
	auto r = sqrt(R.x*R.x + R.y*R.y);


	///<gravitation woooooooooooooo>
	//set the force to the appropriate object
	if (s.getMass() > t.getMass())
		t.setForce(((-(G*M*m) / (r * r*r)) * R));
	else if (s.getMass() < t.getMass())
		s.setForce(((-(G*M*m) / (r * r*r)) * R));

}

void MainScene::gravitate(S_Dot & s, BasecodeTriangle & t, float dt)
{
	//this function is the same, but for the player specifically.
	//we dont need to check which object to apply the force to, since the player will always have a smaller mass
	auto M = s.getMass() > t.getMass() ? s.getMass() : t.getMass();
	auto m = s.getMass() > t.getMass() ? t.getMass() : s.getMass();
	auto R = t.getPosition() - s.getPosition();
	auto r = sqrt(R.x*R.x + R.y*R.y);


	///<gravitation woooooooooooooo>
	t.addForce(((-(G*M*m) / (r * r*r)) * R) / 30, dt);
}

void MainScene::update(float dt)
{

	//spawn blackholes if the size is not equal to the level number
	if (blackholes.size() != levelNumber) {
		spawnBlackholes();
		spawnParticles();
	}

	//spawn more particles if there are less than 100
	if (particles.size() < 100) {
		auto r = 5 + rand() % 10;
		auto mass = ((c*c) / 2 * G) * r;
		particles.push_back(new S_Dot(this, cocos2d::Vec2(rand() % (int)windowSize.x, rand() % (int)windowSize.y), cocos2d::Vec2(0, 0), r, mass, cocos2d::Color4F(0.5f + rand() % 2, 0.5f + rand() % 2, 0.5f + rand() % 2, 1)));
	}

	//gravitate the particles and the player, and update the blackholes and the particles
	for (int i = 0; i < blackholes.size(); ++i) {
		for (int j = 0; j < particles.size(); ++j) {
			gravitate(*blackholes[i], *particles[j]);
			particles[j]->update(dt);
		}
		gravitate(*blackholes[i], *T1, dt);
		blackholes[i]->update(dt);

	}

	checkPlayerInput(dt);
	T1->update(dt);

	//if the player beats the level, go to the next one
	if (T1->getPosition().y >= 1100) {
		T1->setPosition(cocos2d::Vec2(700, 30));
		T1->setForce(cocos2d::Vec2(0, 0));
		levelNumber++;
		levelLabel->setString(std::to_string(levelNumber));
	}


	for (unsigned i = 0; i < blackholes.size(); ++i) {
		//check to see if the player is touching a blackhole
		if (blackholes[i]->checkCollision(*T1->getBox()))
		{
			T1->setPosition(cocos2d::Vec2(700, 30));
			T1->setForce(cocos2d::Vec2(0, 0));
			T1->lives--;
			if (T1->lives == 0)
				gameoverLabel->setVisible(true);
		}
		for (unsigned j = 0; j < particles.size(); ++j) {
			//if particles are touching blackholes, remove them
			if (blackholes[i]->checkCollision(*particles[j])) {
				delete particles[j];
				particles.erase(particles.begin() + j);
				j--;
			}
		}
	}
}
