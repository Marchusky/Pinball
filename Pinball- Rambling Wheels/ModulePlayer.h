#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleTextures.h"
#include "Box2D/Box2D/Box2D.h"
#include "p2List.h"

#define Ball_x 572
#define Ball_y 750
#define Ball_radius 13

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	PhysBody*		Ball;

	iPoint			ball_position;

	SDL_Texture*	ball_tex;
	SDL_Texture*	points;

	char			high_score[20];
	char			score[20];

	uint32			high_score_points = 0;
	uint32			score_points = 0;

	int				score_font = -1;
	int				high_score_font = -1;

	int				lives;
	bool			dead = false;
	uint			dead_fx;

	void SetBallPosition(int x, int y);

private:
	void Lives();
};