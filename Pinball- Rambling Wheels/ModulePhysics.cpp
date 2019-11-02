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
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	//---WORLD CREATION---//
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	//---MAP BORDERS---//

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(0, 0);

	b2Body* b = world->CreateBody(&body);

	b2Vec2 v1(PIXEL_TO_METERS(0.0f), PIXEL_TO_METERS(0.0f));
	b2Vec2 v2(PIXEL_TO_METERS(600.0f), PIXEL_TO_METERS(0.0f));
	b2Vec2 v3(PIXEL_TO_METERS(600.0f), PIXEL_TO_METERS(900.0f));
	b2Vec2 v4(PIXEL_TO_METERS(0.0f), PIXEL_TO_METERS(900.0f));
	b2Vec2 v5(PIXEL_TO_METERS(550.0f), PIXEL_TO_METERS(900.0f));

	b2EdgeShape edge1; 		edge1.Set(v1, v4);
	b2EdgeShape edge2;		edge2.Set(v4, v5);
	b2EdgeShape edge3;		edge3.Set(v2, v3);
	b2EdgeShape edge4;		edge4.Set(v1, v2);


	b2FixtureDef fixture1;	fixture1.shape = &edge1;
	b2FixtureDef fixture2;	fixture2.shape = &edge2;
	b2FixtureDef fixture3;	fixture3.shape = &edge3;
	b2FixtureDef fixture4;	fixture4.shape = &edge4;
 

	b->CreateFixture(&fixture1);
	b->CreateFixture(&fixture2);
	b->CreateFixture(&fixture3);
	b->CreateFixture(&fixture4);

	//Map borders
	int Back[88] = {
	555, 1000,
	555, 437,
	558, 311,
	556, 254,
	540, 206,
	524, 172,
	492, 129,
	457, 102,
	443, 108,
	433, 126,
	445, 152,
	466, 202,
	481, 258,
	483, 314,
	478, 378,
	462, 427,
	445, 463,
	541, 557,
	545, 761,
	536, 777,
	515, 797,
	388, 899,
	173, 898,
	22, 780,
	13, 767,
	11, 755,
	10, 545,
	112, 448,
	84, 375,
	71, 313,
	74, 261,
	83, 212,
	108, 152,
	159, 87,
	216, 42,
	305, 23,
	402, 30,
	463, 61,
	514, 99,
	554, 157,
	578, 216,
	582, 276,
	584, 393,
	584, 1000
	};
	App->physics->CreateChain(0, 0, Back, 88);

	//---SPRING CREATION---//

	//--Bodies for the spring fixture---//

	b2BodyDef sBody1_def;
	sBody1_def.type = b2_staticBody;
	sBody1_def.position.Set(PIXEL_TO_METERS(575.0f), PIXEL_TO_METERS(940.0f));

	b2Body* sBody1 = world->CreateBody(&sBody1_def);

	b2PolygonShape sShape1;
	sShape1.SetAsBox(PIXEL_TO_METERS(20.0f), PIXEL_TO_METERS(1.0f));

	b2FixtureDef sFixture1;
	sFixture1.shape = &sShape1;

	sBody1->CreateFixture(&sFixture1);

	b2BodyDef sBody2_def;
	sBody2_def.type = b2_dynamicBody;
	sBody2_def.position.Set(PIXEL_TO_METERS(580.0f), PIXEL_TO_METERS(805.0f));
	
	sBody2 = world->CreateBody(&sBody2_def);

	b2PolygonShape sShape2;
	sShape2.SetAsBox(PIXEL_TO_METERS(7.0f), PIXEL_TO_METERS(5.0f));
	b2PolygonShape sShape3;
	sShape3.SetAsBox(PIXEL_TO_METERS(4.0f), PIXEL_TO_METERS(35.0f));

	b2FixtureDef sFixture2;
	sFixture2.shape = &sShape2;
	sFixture2.density = 5;
	sBody2->CreateFixture(&sFixture2);

	b2FixtureDef sFixture3;
	sFixture3.shape = &sShape3;
	sFixture2.density = 5;
	sBody2->CreateFixture(&sFixture3);

	//--Borders----------------------------------------------------------------//

	b2BodyDef bBody1_def;
	bBody1_def.type = b2_staticBody;
	bBody1_def.position.Set(PIXEL_TO_METERS(560.5f), PIXEL_TO_METERS(920.0f));

	b2Body* bBody1 = world->CreateBody(&bBody1_def);

	b2PolygonShape bShape;
	bShape.SetAsBox(PIXEL_TO_METERS(3.0f), PIXEL_TO_METERS(150.0f));

	b2FixtureDef bFixture1;
	bFixture1.shape = &bShape;

	bBody1->CreateFixture(&bFixture1);

	b2BodyDef bBody2_def;
	bBody2_def.type = b2_staticBody;
	bBody2_def.position.Set(PIXEL_TO_METERS(582.0f), PIXEL_TO_METERS(920.0f));

	b2Body* bBody2 = world->CreateBody(&bBody2_def);

	b2FixtureDef bFixture2;
	bFixture2.shape = &bShape;
	
	bBody2->CreateFixture(&bFixture2);

	b2BodyDef bBody3_def;
	bBody3_def.type = b2_staticBody;
	bBody3_def.position.Set(PIXEL_TO_METERS(562.0f), PIXEL_TO_METERS(770.0f));

	b2Body* bBody3 = world->CreateBody(&bBody3_def);

	b2PolygonShape bShape2;
	bShape2.SetAsBox(PIXEL_TO_METERS(2.0f), PIXEL_TO_METERS(1.0f));

	b2FixtureDef bFixture3;
	bFixture3.shape = &bShape2;

	bBody3->CreateFixture(&bFixture3);

	b2BodyDef bBody4_def;
	bBody4_def.type = b2_staticBody;
	bBody4_def.position.Set(PIXEL_TO_METERS(580.0f), PIXEL_TO_METERS(770.0f));

	b2Body* bBody4 = world->CreateBody(&bBody4_def);

	b2FixtureDef bFixture4;
	bFixture4.shape = &bShape2;

	bBody4->CreateFixture(&bFixture4);


	//--Fixture(hopefully a spring)------------------------------------------//

	b2Vec2 sAnchor1 = sBody1->GetWorldCenter();
	b2Vec2 sAnchor2 = sBody2->GetWorldCenter();

	b2DistanceJointDef jointDef;
	jointDef.Initialize(sBody1, sBody2, sAnchor1, sAnchor2);
	jointDef.collideConnected = true;
	jointDef.bodyA = sBody1;
	jointDef.bodyB = sBody2;
	jointDef.frequencyHz = 2.0f;
	jointDef.dampingRatio = 0.3f;

	b2DistanceJoint* joint = (b2DistanceJoint*)world->CreateJoint(&jointDef);

	// TODO 3: You need to make ModulePhysics class a contact listener

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		forceON = true;

	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		forceON = false;
		sBody2->ApplyForce(b2Vec2(0, -5000), sBody2->GetWorldCenter(), true);
	}

	if(forceON)
	{
		sBody2->ApplyForce(b2Vec2(0, 1000), sBody2->GetWorldCenter(), true);
	}
	// TODO: HomeWork
	/*
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
	}
	*/

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, float density)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = density;

	b->CreateFixture(&fixture);

	// TODO 4: add a pointer to PhysBody as UserData to the body
	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
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
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
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
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
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
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x),(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
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
		}
	}

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
	// TODO 1: Write the code to return true in case the point
	// is inside ANY of the shapes contained by this body
	b2Transform transform;
	transform.SetIdentity();
	b2Vec2 point(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Fixture* fixture = body->GetFixtureList();

	bool hit = NULL;
	//-----------------------------------------------------------

	for (fixture; fixture; fixture = fixture->GetNext())
	{
		b2Shape* f_shape = fixture->GetShape();

		hit = f_shape->TestPoint(body->GetTransform(), point);
		if (hit == true)
		{
			return hit;
		}
	}
	
	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	// TODO 2: Write code to test a ray cast between both points provided. If not hit return -1
	// if hit, fill normal_x and normal_y and return the distance between x1,y1 and it's colliding point
	b2Transform transform;
	transform.SetIdentity();
	b2Fixture* fixture = body->GetFixtureList();

	b2RayCastInput input;
	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	int32 childIndex = 0;
	b2RayCastOutput output;
	bool hit = nullptr;

	for (fixture; fixture; fixture = fixture->GetNext())
	{
		b2Shape* f_shape = fixture->GetShape();

		hit = f_shape->RayCast(&output, input, body->GetTransform(), childIndex);
		if (hit)
		{
			b2Vec2 hitPoint = input.p1 + output.fraction * (input.p2 - input.p1);
			
		
		}
	}

	return hit;
}

// TODO 3

// TODO 7: Call the listeners that are not NULL