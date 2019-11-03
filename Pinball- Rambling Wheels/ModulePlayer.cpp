#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball_tex = App->textures->Load("pinball/ball_tex.png");


	//---Da Ball-------------------------------------------------------------//
	Ball = App->physics->CreateCircle(Ball_x, Ball_y, Ball_radius, 0.1f);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");




	App->fonts->Unload(score_font);
	App->fonts->Unload(high_score_font);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}



