#include "Bar.h"


// constructor
//----------------------------------------
Bar::Bar(const int wid, const int hei)
{
	rect.h = 15;
	rect.w = 100;

	rect.x = (wid / 2) - (rect.w / 2);
	rect.y = hei - (rect.h * 9);

	posX = rect.x;

	//assign reset pos.
	resetPositionX = rect.x;
	resetPositionY = rect.y;
	
	windowHeight = hei;
	windowWidth = wid;
}


// destructor
//----------------------------------------
Bar::~Bar()
{

}


// UPDATE
//----------------------------------------
void Bar::Update(SDL_Event* control, const  Timer* Time, const Uint8* keyboard_state_array)
{

	if (control->type == SDL_KEYDOWN)
	{

		if (keyboard_state_array[SDL_SCANCODE_LEFT])
		{
			posX -= barSpeed * Time->deltaTime;

			// clamping movement left side.
			if (posX < 0)
			{
				posX = 0;
			}

			rect.x = posX;


			return;
		}
		else if (keyboard_state_array[SDL_SCANCODE_RIGHT])
		{
			posX += barSpeed * Time->deltaTime;
			
			// clamping movement right side.
			if (posX + rect.w > windowWidth)
			{
				posX = windowWidth - rect.w;
			}

			rect.x = posX;
			return;
		}
	}
	
//	std::cout << Time->deltaTime << std::endl;
}


// DRAW
//----------------------------------------
void Bar::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(renderer, &rect);
}


//----------------------------------------
float Bar::GetSpeedX()
{
	return barSpeed;
}


// CheckPositionsInside
//----------------------------------------
bool Bar::CheckPositionInside( int _positionCheckX, int _positionCheckY)
{
	if (_positionCheckX >= rect.x && _positionCheckX <= (rect.x + rect.w) &&
		_positionCheckY >= rect.y && _positionCheckY <= (rect.y + rect.h)  )
	{
		//std::cout << "punto dentro en altura" << std::endl;
		return true;
	}

	return false;
}

// ResetPosition
//----------------------------------------
bool Bar::ResetPosition()
{
	rect.x = resetPositionX;
	rect.y = resetPositionY;
	posX   = rect.x;

	return false;
}