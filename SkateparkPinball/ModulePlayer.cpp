#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include"ModuleRender.h"
#include "ModuleTextures.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{

	circle = App->textures->Load("pinball/ball.png");
	b2BodyDef bd;
	ground = App->physics->world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = 568;
	int y = 406;
	int radius = 19;

	ball=App->physics->CreateCircle(x, y, radius * 0.5f,b2_dynamicBody, NONE);

	
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	App->textures->Unload(circle);
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int x, y;
	ball->GetPosition(x, y);
	App->renderer->Blit(circle, x, y, NULL, 1.0f, ball->GetRotation());

	return UPDATE_CONTINUE;
}



