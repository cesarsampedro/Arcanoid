#pragma once

#include <iostream>
#include <SDL.h>
#include "Timer.h"

class Bar
{
public:
	Bar(const int wid,const int hei);
	~Bar();
	float GetSpeedX();
	SDL_Rect rect;

	void Update(SDL_Event* control,const   Timer* Time,  const Uint8* keyboard_state_array);
	void Draw(SDL_Renderer* renderer);
	bool CheckPositionInside(int _positionCheckX, int _positionCheckY);
	bool ResetPosition();
private:
	
	float posX = 0;
	const float barSpeed = 330;

	int resetPositionX = 0;
	int resetPositionY = 0;

	int windowWidth;
	int windowHeight;

};