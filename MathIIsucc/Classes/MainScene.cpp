#include "MainScene.h"
#include "DisplayHandler.h"
#include "InputHandler.h"
#include <iostream>

//--- Static Constants ---//
float MainScene::degToRad = 3.14159f / 180.0f;
float MainScene::radToDeg = 180.0f / 3.14159f;
float MainScene::gravity = 98.0f;


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

	//Call our own init functions
	initCocosReferences();
	initPrivateVariables();
	initScene();

	//Make the background of our scene white instead of the default black
	director->setClearColor(Color4F(255, 255, 255, 255));

	//Schedule the use of the update function so the function actually gets called
	this->scheduleUpdate();
	
	//Let Cocos know that the init function was successful
	return true;
}

void MainScene::update(float deltaTime)
{
	//Update the planets
	updatePlanets(deltaTime);

	//Get ready for the next frame of inputs
	INPUTS->clearForNextFrame();
}



//--- Init Functions ---//
void MainScene::initCocosReferences()
{
	//Store the director singleton for easy access
	director = Director::getInstance();
}

void MainScene::initPrivateVariables()
{
	//Init the sun's information
	sunPosition = DISPLAY->getWindowSizeAsVec2() / 2.0f;
	sunRadius = 70.0f;
	M = 1000000.0f;
	G = 1.0f;
}

void MainScene::initScene()
{
	//Store the window dimensions so we don't have to call the same function a bunch of times
	Vec2 windowSize = DISPLAY->getWindowSizeAsVec2();

	//Init the sun
	sun = PhysicsCircle(this, sunPosition, sunRadius, M, Color4F(1.0f, 0.8f, 0.0f, 1.0f));

	//Init the planets
	planets[0] = PhysicsCircle(this, Vec2(sunPosition.x + sunRadius * 1.2f, sunPosition.y), 6.0f, 3.0f, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
	planets[0].setVelocity(Vec2(0.0f, 110.f));
	planets[1] = PhysicsCircle(this, Vec2(sunPosition.x + sunRadius * 1.7f, sunPosition.y), 10.0f, 10.0f, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	planets[1].setVelocity(Vec2(0.0f, 100.0f));
	planets[2] = PhysicsCircle(this, Vec2(sunPosition.x + sunRadius * 3.0f, sunPosition.y), 12.0f, 15.0f, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	planets[2].setVelocity(Vec2(0.0f, -70.0f));
}



//--- Update Functions ---//
void MainScene::updatePlanets(float _dt)
{
	//Apply the gravity forces to the planets, using the equation
	applyGravityToPlanets();

	//Loop through and update the planets
	for (int i = 0; i < NUM_PLANETS; i++)
		planets[i].update(_dt);
}



//--- Methods ---//
void MainScene::applyGravityToPlanets()
{
	//Loop through the planets and apply the calculated gravitational force to them
	for (int i = 0; i < NUM_PLANETS; i++)
	{
		float m1 = M; //sun's mass
		float m2 = planets[i].getMass(); //planet's mass
		Vec2 r = planets[i].getPosition() - sunPosition; //vector between the sun and the planet

		Vec2 force = r * ((-G * m1 * m2) / (r.lengthSquared() * r.length()));

		planets[i].setForce(force);
	}
}