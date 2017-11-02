#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = 0;// -SCREEN_WIDTH / 2;
	int y = 0;// -SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* big_ball = world->CreateBody(&body);
	float size = 1.75f;
	//b2CircleShape shape;
	//shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;


	//FLIPPERS D=down T=top R=right L=left
	b2Vec2 flipperDR[9];
	flipperDR[0] = { PIXEL_TO_METERS(306), PIXEL_TO_METERS(797) };
	flipperDR[1] = { PIXEL_TO_METERS(376), PIXEL_TO_METERS(781) };
	flipperDR[2] = { PIXEL_TO_METERS(379), PIXEL_TO_METERS(790) };
	flipperDR[3] = { PIXEL_TO_METERS(383), PIXEL_TO_METERS(799) };
	flipperDR[4] = { PIXEL_TO_METERS(380), PIXEL_TO_METERS(810) };
	flipperDR[5] = { PIXEL_TO_METERS(372), PIXEL_TO_METERS(813) };
	flipperDR[6] = { PIXEL_TO_METERS(356), PIXEL_TO_METERS(812) };
	flipperDR[7] = { PIXEL_TO_METERS(314), PIXEL_TO_METERS(806) };
	flipperDR[8] = { PIXEL_TO_METERS(307), PIXEL_TO_METERS(803) };

	dr_flipper_anchor = App->physics->CreateCircle(370, 801, 2, b2_staticBody, NONE);
	dr_flipper = App->physics->CreatePolygon(flipperDR, 8, 0);

	b2RevoluteJointDef dr_jointdef;
	dr_jointdef.bodyA = dr_flipper->body;
	dr_jointdef.bodyB = dr_flipper_anchor->body;
	dr_jointdef.localAnchorA.Set(PIXEL_TO_METERS(370), PIXEL_TO_METERS(801));
	dr_jointdef.enableLimit = true;
	dr_jointdef.lowerAngle = -60 * DEGTORAD;
	dr_jointdef.upperAngle = 10 * DEGTORAD;

	dr_revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&dr_jointdef);



	b2Vec2 flipperDL[9];
	flipperDL[0] = { PIXEL_TO_METERS(206), PIXEL_TO_METERS(786) };
	flipperDL[1] = { PIXEL_TO_METERS(203), PIXEL_TO_METERS(791) };
	flipperDL[2] = { PIXEL_TO_METERS(200), PIXEL_TO_METERS(801) };
	flipperDL[3] = { PIXEL_TO_METERS(202), PIXEL_TO_METERS(810) };
	flipperDL[4] = { PIXEL_TO_METERS(212), PIXEL_TO_METERS(815) };
	flipperDL[5] = { PIXEL_TO_METERS(270), PIXEL_TO_METERS(806) };
	flipperDL[6] = { PIXEL_TO_METERS(277), PIXEL_TO_METERS(804) };
	flipperDL[7] = { PIXEL_TO_METERS(277), PIXEL_TO_METERS(797) };
	flipperDL[8] = { PIXEL_TO_METERS(225), PIXEL_TO_METERS(787) };

	dl_flipper_anchor = App->physics->CreateCircle(214, 801, 2, b2_staticBody, NONE);
	dl_flipper = App->physics->CreatePolygon(flipperDL, 8, 0);

	b2RevoluteJointDef dl_jointdef;
	dl_jointdef.bodyA = dl_flipper->body;
	dl_jointdef.bodyB = dl_flipper_anchor->body;
	dl_jointdef.localAnchorA.Set(PIXEL_TO_METERS(214), PIXEL_TO_METERS(801));
	dl_jointdef.enableLimit = true;
	dl_jointdef.lowerAngle = -10 * DEGTORAD; //cambiar angulos luego de borrar parte del mapa
	dl_jointdef.upperAngle = 60 * DEGTORAD;

	dl_revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&dl_jointdef);


	b2Vec2 flipperTR[8];
	flipperTR[0] = { PIXEL_TO_METERS(480), PIXEL_TO_METERS(440) };
	flipperTR[1] = { PIXEL_TO_METERS(424), PIXEL_TO_METERS(473) };
	flipperTR[2] = { PIXEL_TO_METERS(425), PIXEL_TO_METERS(478) };
	flipperTR[3] = { PIXEL_TO_METERS(431), PIXEL_TO_METERS(479) };
	flipperTR[4] = { PIXEL_TO_METERS(486), PIXEL_TO_METERS(468) };
	flipperTR[5] = { PIXEL_TO_METERS(497), PIXEL_TO_METERS(460) };
	flipperTR[6] = { PIXEL_TO_METERS(498), PIXEL_TO_METERS(452) };
	flipperTR[7] = { PIXEL_TO_METERS(491), PIXEL_TO_METERS(440) };
	

	tr_flipper_anchor = App->physics->CreateCircle(485, 454, 2, b2_staticBody, NONE);
	tr_flipper = App->physics->CreatePolygon(flipperTR, 7, 0);

	b2RevoluteJointDef tr_jointdef;
	tr_jointdef.bodyA = tr_flipper->body;
	tr_jointdef.bodyB = tr_flipper_anchor->body;
	tr_jointdef.localAnchorA.Set(PIXEL_TO_METERS(485), PIXEL_TO_METERS(454));
	tr_jointdef.enableLimit = true;
	tr_jointdef.lowerAngle = -60 * DEGTORAD;
	tr_jointdef.upperAngle = 10 * DEGTORAD;

	tr_revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&tr_jointdef);



	b2Vec2 flipperTL[9];
	flipperTL[0] = { PIXEL_TO_METERS(97), PIXEL_TO_METERS(340) };
	flipperTL[1] = { PIXEL_TO_METERS(46), PIXEL_TO_METERS(316) };
	flipperTL[2] = { PIXEL_TO_METERS(37), PIXEL_TO_METERS(306) };
	flipperTL[3] = { PIXEL_TO_METERS(38), PIXEL_TO_METERS(293) };
	flipperTL[4] = { PIXEL_TO_METERS(51), PIXEL_TO_METERS(287) };
	flipperTL[5] = { PIXEL_TO_METERS(62), PIXEL_TO_METERS(293) };
	flipperTL[6] = { PIXEL_TO_METERS(80), PIXEL_TO_METERS(311) };
	flipperTL[7] = { PIXEL_TO_METERS(104), PIXEL_TO_METERS(335) };
	flipperTL[8] = { PIXEL_TO_METERS(102), PIXEL_TO_METERS(340) };

	tl_flipper_anchor = App->physics->CreateCircle(50, 302, 2, b2_staticBody, NONE);
	tl_flipper = App->physics->CreatePolygon(flipperTL, 8, 0);

	b2RevoluteJointDef tl_jointdef;
	tl_jointdef.bodyA = tl_flipper->body;
	tl_jointdef.bodyB = tl_flipper_anchor->body;
	tl_jointdef.localAnchorA.Set(PIXEL_TO_METERS(50), PIXEL_TO_METERS(302));
	tl_jointdef.enableLimit = true;
	tl_jointdef.lowerAngle = -10 * DEGTORAD; //cambiar angulos luego de borrar parte del mapa
	tl_jointdef.upperAngle = 60 * DEGTORAD;



	//*******

	b2Filter filterflipper;
	filterflipper.categoryBits = WALL;
	filterflipper.maskBits = BALL;
	dr_flipper->body->GetFixtureList()->SetFilterData(filterflipper);
	dl_flipper->body->GetFixtureList()->SetFilterData(filterflipper);
	tr_flipper->body->GetFixtureList()->SetFilterData(filterflipper);
	tl_flipper->body->GetFixtureList()->SetFilterData(filterflipper);



	//*******
	tl_revolutejoint = (b2RevoluteJoint*)world->CreateJoint(&tl_jointdef);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if (pb1 && pb2 && pb1->listener) {
				pb1->listener->OnCollision(pb1, pb2);
			
			}
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, b2BodyType type, COLL_TYPE collider_type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	
	

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->coll = collider_type;
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, b2BodyType type, COLL_TYPE collider_type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	
	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);
	
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;
	pbody->coll = collider_type;

	return pbody;

}
PhysBody* ModulePhysics::CreateCBounce(int x, int y, int radius, float f_restitution, b2BodyType type, COLL_TYPE collider_type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));



	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.restitution = f_restitution;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->coll = collider_type;
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateBounce(int x, int y, int* points, int size, float f_restitution, b2BodyType type, COLL_TYPE collider_type) {
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));


	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.restitution = f_restitution;
	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;
	pbody->coll = collider_type;

	return pbody;
}


PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height,COLL_TYPE collider_type)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;
	pbody->coll = collider_type;
	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType type, COLL_TYPE collider_type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;
	pbody->coll = collider_type;

	return pbody;
}

PhysBody* ModulePhysics::CreatePolygon(b2Vec2 vertices[], uint num_vecs, float angle) {

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(0, 0);
	body.angle = angle * DEGTORAD;

	b2Body* b = App->physics->world->CreateBody(&body);
	b2PolygonShape polygon;
	polygon.Set(vertices, num_vecs);

	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.shape = &polygon;
	b->CreateFixture(&fixture);
	
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = 0;
	pbody->height = 0;
	
	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN )
			{
				b2Vec2 mousepos;
				mousepos.x = PIXEL_TO_METERS(App->input->GetMouseX());
				mousepos.y= PIXEL_TO_METERS(App->input->GetMouseY());

				if (f->TestPoint(mousepos)) {
					b2MouseJointDef def;
					def.bodyA = ground;
					def.bodyB = f->GetBody();
					def.target = mousepos;
					def.dampingRatio = 0.5f;
					def.frequencyHz = 2.0f;
					def.maxForce = 100.0f * f->GetBody()->GetMass();
					mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
				}
			}
			// test if the current body contains mouse position
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mouse_joint != NULL) {
				b2Vec2 mousepos;
				mousepos.x = PIXEL_TO_METERS(App->input->GetMouseX());
				mousepos.y = PIXEL_TO_METERS(App->input->GetMouseY());

				b2Vec2 anchorA = mouse_joint->GetAnchorA();
				b2Vec2 anchorB = mouse_joint->GetAnchorB();
				
				mouse_joint->SetTarget(mousepos);
				App->renderer->DrawLine(METERS_TO_PIXELS(anchorA.x), METERS_TO_PIXELS(anchorA.y), METERS_TO_PIXELS(anchorB.x), METERS_TO_PIXELS(anchorB.y), 255,0,0,255);
				
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && mouse_joint != NULL) {
				world->DestroyJoint(mouse_joint);
				mouse_joint = nullptr;
			}
		}
	}
	/*
	modulephys (esto es b2contactlisener o algo asi)
    phys body
addbody->densidad y restitucion para ver cuanto bota


modulescene
   paredes, barr, bounces, bonus->isSensor=true,

moduleplayer
    flippers, bola--bullet checkea colisiones mas contiuamente(hacer bullet=true), 

tiene q tener fin de partida y puntuación
queremos dentro de los modulos tener un Module*listener o algo asi para las colisiones, entonces poner un oncollision en el module player

b2body applyforce to caster para muelle?
b2body apluanglular impulse para los flipers y muelle de la bola.
	*/
	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	

	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	
	// TODO 4: If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}