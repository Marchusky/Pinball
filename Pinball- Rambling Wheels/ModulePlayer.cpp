#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	lives = 3;

	ball_tex = App->textures->Load("pinball/ball_tex.png");

	//---Da Ball-------------------------------------------------------------//
	SetBallPosition(Ball_x, Ball_y);


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");


	App->fonts->UnLoad(score_font);
	App->fonts->UnLoad(high_score_font);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Lives();

	if (Ball != NULL)
	{
		int x, y;
		Ball->GetPosition(x, y);
		App->renderer->Blit(ball_tex, x - 3, y - 2, NULL, 1.0f, Ball->GetRotation());
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::SetBallPosition(int x, int y)
{
	Ball = App->physics->CreateCircle(Ball_x, Ball_y, Ball_radius, 0.1f);
	App->renderer->Blit(ball_tex, Ball_x - 3, Ball_y - 2, NULL, 1.0f, Ball->GetRotation());
}

void ModulePlayer::Lives()
{
	if (Ball_y < 900)
	{
		dead = false;
	}
	else if (Ball_y >= 900 && !dead)
	{
		dead = true;
		lives--; //correcto?

		if (lives != 0)
		{
			App->audio->PlayFx(dead_fx);
			SetBallPosition(Ball_x, Ball_y);
		}
		else
		{
			//Actualice highscore at the end of a game
			if (high_score_points < score_points)
			{
				high_score_points = score_points;
			}
			//Print score & highscore
			if (App->input->GetKey(SDL_SCANCODE_SPACE))
			{
				SetBallPosition(Ball_x, Ball_y);
				lives = 5;
				score_points = 0;
			}
		}
	}
}