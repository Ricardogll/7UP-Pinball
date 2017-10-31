#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -10.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies

enum COLL_TYPE {
	NONE = -1,
	BALL,
	WALL,
	BOUNCE,
};

class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	COLL_TYPE coll;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type, COLL_TYPE collider_type);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type, COLL_TYPE collider_type);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size, b2BodyType type, COLL_TYPE collider_type);
	PhysBody* CreateBounce(int x, int y, int* points, int size, float f_restitution, b2BodyType type, COLL_TYPE collider_type);
	PhysBody* CreateCBounce(int x, int y, int radius, float f_restitution, b2BodyType type, COLL_TYPE collider_type);
	PhysBody* CreatePolygon(b2Vec2 vertices[], uint num_vecs, float angle);
	//PhysBody* CreateBounce(int x, int y, int width, int height, b2BodyType type, COLL_TYPE collider_type);
	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;
private:

	bool debug;
	
	b2MouseJoint* mouse_joint;
	b2Body* ground;

	PhysBody* dr_flipper;
	PhysBody* dr_flipper_anchor;
	b2RevoluteJoint* dr_revolutejoint;

	PhysBody* dl_flipper;
	PhysBody* dl_flipper_anchor;
	b2RevoluteJoint* dl_revolutejoint;

	PhysBody* tr_flipper;
	PhysBody* tr_flipper_anchor;
	b2RevoluteJoint* tr_revolutejoint;

	PhysBody* tl_flipper;
	PhysBody* tl_flipper_anchor;
	b2RevoluteJoint* tl_revolutejoint;
};