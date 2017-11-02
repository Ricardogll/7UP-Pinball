//#pragma once
//#include "Module.h"
//#include "Globals.h"
//#include "p2Point.h"
//
//class ModulePlayer : public Module
//{
//public:
//	ModulePlayer(Application* app, bool start_enabled = true);
//	virtual ~ModulePlayer();
//
//	bool Start();
//	update_status Update();
//	bool CleanUp();
//
//public:
//
//};

#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "ModuleTextures.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void loselife();

	bool lose_life = false;
	bool ball_in_start = true;
	int points = 0;
	int highscore = 0;
	PhysBody* ball;
	int lifes = 2;
	
private:
	
	SDL_Texture* circle;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
};