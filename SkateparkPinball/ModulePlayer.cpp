#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	b2BodyDef bd;
	ground = App->physics->world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = 568;
	int y = 406;
	int diameter = 19;

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.bullet = true;
	
	b2Body* playerball = App->physics->world->CreateBody(&body);
	playerball->SetBullet(true);
	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;
	
	b2FixtureDef fixture;
	fixture.shape = &shape;
	playerball->CreateFixture(&fixture);
	fixture.density = -0.5;
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}



