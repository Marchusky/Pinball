#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"

#define MAX_FRAMES 50

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];


private:
	float current_frame;
	bool end_animation = false;
	int last_frame = 0;
	int num_frames = 0;
	int loops = 0;

public:

	// Defines the last frame as the rect.
	void PushBack(const SDL_Rect &rect)
	{
		frames[last_frame++] = rect;
	}

	void SetWidth(const int & width)
	{
		for (int i = 0; i < num_frames; ++i) {
			frames[i].w = width;
		}
	}

	// Returns a rect with current position of the frame.
	SDL_Rect &GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			end_animation = true;
			loops++;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
		loops = 0;
	}

	// This function sets an ended animation to end. needed?
	void SetAnimation(bool ended) {

		end_animation = ended;
	}

	// This function gets the animation a returns it to end once the last frame is over. needed?
	bool GetAnimation() {

		return end_animation;
	}
};

#endif