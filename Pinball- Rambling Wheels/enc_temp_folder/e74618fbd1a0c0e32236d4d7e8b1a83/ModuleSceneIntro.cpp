#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ball_tex = circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("sprites/background sprites.png");
	ball_tex = App->textures->Load("pinball/ball_tex.png");
	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	// TODO: Homework - create a sensor

	//---Da Ball-------------------------------------------------------------//
	//Ball = App->physics->CreateCircle(572.5f, 750.0f, 11, 0.1f);

	//------------------------------------------------------------------------------------------------------//
	//---------------------------------O B S T A C L E S---------------------------------------------------//
	//----------------------------------------------------------------------------------------------------//
	PhysBody* cats_3000 = App->physics->CreateCircle(276.5f, 195.0f, 40, 0.1f, b2_staticBody);
	PhysBody* cats_2000 = App->physics->CreateCircle(367.3f, 271.0f, 40, 0.1f, b2_staticBody);
	PhysBody* cats_1000 = App->physics->CreateCircle(289.3f, 344.8f, 40, 0.1f, b2_staticBody);
	
	int bottom_left[24] = {
	168,834, 171,822, 153,805, 117,776,	73,742, 59,716,
	54,690,	52,742, 55,755, 72,770, 149,832, 159,838 };

	App->physics->CreateChain(0, 0, bottom_left, 24);
	
	int bottom_right[28] = {
	501,691, 499,707, 492,726, 482,742, 388,817, 384,826, 386,834,
	393,837, 401,836, 496,760, 501,751, 502,746, 504,698 };

	App->physics->CreateChain(0, 0, bottom_right, 26);

	int first_light[14] = {
	273,86, 267,90, 267,117, 273,122, 279,117, 279,90	};

	App->physics->CreateChain(0, 0, first_light, 12);

	int second_light[14] = {
	44+273,-1+86, 44+267,-1+90, 44+267,-1+117,
	44+273,-1+122, 44+279,-1+117, 44+279,-1+90 };

	App->physics->CreateChain(0, 0, second_light, 12);

	int third_light[14] = {
	88+273,-2+86, 88+267,-2+90, 88+267,-2+117,
	88+273,-2+122, 88+279,-2+117, 88+279,-2+90 };

	App->physics->CreateChain(0, 0, third_light, 12);

	int left_most_obstacle[22] = {
	133,200, 119,232, 112,290, 117,335, 134,383,
	147, 412, 171,403, 154,341, 144,290, 136,246 };

	App->physics->CreateChain(0, 0, left_most_obstacle, 20);

	int left_obstacle[30] = {
	236,84, 193,116, 176,135, 176,181, 186,260, 202,335, 218,384,
	243,376, 239,371, 226,348, 207,293, 200,230, 207,155, 221, 116 };

	App->physics->CreateChain(0, 0, left_obstacle, 28);

	int red_triangle_right[28] = {
	461, 703,
	461, 635,
	456, 630,
	449, 630,
	444, 635,
	373, 762,
	373, 767,
	375, 773,
	380, 775,
	385, 775,
	455, 720,
	458, 715,
	460, 711
	};

	App->physics->CreateChain(0, 0, red_triangle_right, 26);

	// Pivot 0, 0
	int red_trieangle_left[28] = {
		98, 629,
		105, 630,
		110, 636,
		126, 662,
		155, 719,
		179, 764,
		180, 770,
		175, 775,
		168, 775,
		98, 719,
		94, 713,
		93, 705,
		93, 634
	};

	App->physics->CreateChain(0, 0, red_trieangle_left, 26);
	//-------------------------DO ALL PUSHBACKS FROM THE BACKGROUND-----------------------------------------//
	
	background_an.PushBack({ 0, 0, 600, 900 });
	background_an.PushBack({ 600, 0, 600, 900 });
	background_an.PushBack({ 1202, -1, 600, 900 });
	background_an.PushBack({ 1802, 0, 600, 900 });
	//background_an.PushBack({ 0, 900, 600, 900 });
	//background_an.PushBack({ 601, 900, 600, 900 });
	//background_an.PushBack({ 1201, 900, 600, 900 });
	//background_an.PushBack({ 1801, 900, 600, 900 });
	background_an.speed = 0.01f;
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//TEMPORALY BLIT THE BACKGROUND
	SDL_Rect rect;
	rect.h = 900;
	rect.w = 600;
	rect.x = rect.y = 0;

	App->renderer->Blit(background, 0, 0, &rect);
	//App->renderer->Blit(background, 0, 0, &background_an.GetCurrentFrame());
	
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();

	}
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_UP)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		// TODO 8: Make sure to add yourself as collision callback to the circle you creates
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------

	if (Ball != NULL)
	{
		int x, y;
		Ball->GetPosition(x, y);
		App->renderer->Blit(ball_tex, x-3, y-2, NULL, 1.0f, Ball->GetRotation());
	}
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

// TODO 8: Now just define collision callback for the circle and play bonus_fx audio
