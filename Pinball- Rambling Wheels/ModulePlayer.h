#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleTextures.h"
#include "Box2D/Box2D/Box2D.h"
#include "p2List.h"

#define Ball_x 572.5f
#define Ball_y 750.0f
#define Ball_radius 11

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	PhysBody* Ball;

	iPoint			player_position;

	SDL_Texture*	ball_tex;
	SDL_Texture*	points;

	char high_score[20];
	char score[20];

	int score_font = -1;
	int high_score_font = -1;

	bool dead = false;
	uint dead_fx;

	
private:
	void SetBallPosition(int x, int y);
	void Lives();
};