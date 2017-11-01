#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include"ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

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

	ball=App->physics->CreateCircle(x, y, radius * 0.5f,b2_dynamicBody, BALL);
	ball->body->SetBullet(true);
	ball->listener = this;
	b2Filter ballfilter;
	ballfilter.categoryBits = BALL;
	ballfilter.maskBits = -1;
	ball->body->GetFixtureList()->SetFilterData(ballfilter);

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
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		App->physics->dl_revolutejoint->GetBodyA()->ApplyAngularImpulse(-0.75, true);
		App->physics->tl_revolutejoint->GetBodyA()->ApplyAngularImpulse(-0.75, true);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		App->physics->dr_revolutejoint->GetBodyA()->ApplyAngularImpulse(0.75f, true);
		App->physics->tr_revolutejoint->GetBodyA()->ApplyAngularImpulse(0.75f, true);
	}
	


	int x, y;
	ball->GetPosition(x, y);
	App->renderer->Blit(circle, x, y, NULL, 1.0f, ball->GetRotation());

	if (lose_life && ball!=nullptr)
		loselife();


	return UPDATE_CONTINUE;
}


void ModulePlayer::loselife() {

	/*App->physics->world->DestroyBody(ball->body);
	ball = nullptr;*/

	if (lifes != 0) {

		App->physics->world->DestroyBody(ball->body);
		ball = nullptr;


		int x = 568;
		int y = 406;
		int radius = 19;

		ball = App->physics->CreateCircle(x, y, radius * 0.5f, b2_dynamicBody, BALL);
		ball->body->SetBullet(true);
		ball->listener = this;
		b2Filter ballfilter;
		ballfilter.categoryBits = BALL;
		ballfilter.maskBits = -1;
		ball->body->GetFixtureList()->SetFilterData(ballfilter);

		lifes -= 1;
		LOG("LIFEEEEEEEEEEEEEEEEEE");
	}

	lose_life = false;
}

