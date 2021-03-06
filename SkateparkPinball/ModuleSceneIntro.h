#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModulePhysics.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;
	bool sensed;
	//SDL_Texture* gameover;
	SDL_Texture* intro;
	SDL_Texture* flipper2;
	SDL_Texture* flipper1;
	SDL_Texture* map;
	SDL_Texture* spring;
	SDL_Texture* power;
	uint bonus_fx;
	uint spring_fx;
	uint flipper_fx;
	uint start_fx;
	uint bounce_fx;
	uint wall_fx;
	uint skatepark_music;
	p2Point<int> ray;
	bool ray_on;
	//bool force = false;
	SDL_Rect maprect;
	SDL_Rect startrect;
	PhysBody* muelle;
	PhysBody* muelle2;
	uint currentTime = 0;
	uint lastTime = 0;
	float spring_force = 0;
	PhysBody* bounce6;
	PhysBody* bounce7;
	PhysBody* lose;
	PhysBody* start;
	bool can_play = false;
};