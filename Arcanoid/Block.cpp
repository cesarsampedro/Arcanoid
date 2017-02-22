#include "Block.h"
#include <stdlib.h>
#include <iostream>

// --------------------------
Color::Color()
{
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	int a = 255;
}


// --------------------------
Color::Color(int _r, int _g, int _b, int _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}


// --------------------------
Color::~Color()
{

}


// Constructor
//-------------------------------
Block::Block()
{
	rectBlock.x = m_posX;
	rectBlock.y = m_posY;
	rectBlock.h = height;
	rectBlock.w = width;

	color.r = rand() % 256;
	color.g = rand() % 256;
	color.b = rand() % 256;
	color.a = 255;
}


//-------------------------------
Block::~Block()
{

}


//-------------------------------
void Block::SetPos(int x, int y)
{
	rectBlock.x = x;
	rectBlock.y = y;

	initPositionX = x;
	initPositionY = y;
}


//-------------------------------
void Block::Draw(SDL_Renderer* renderer)
{
	// Assigns a random color everytime you start.
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(renderer, &rectBlock);
}


// --------------------------
void Block::SetColor(Color* _color)
{
	color.r = _color->r;
	color.g = _color->g;
	color.b = _color->b;
	color.a = 255;
}


// --------------------------
bool Block::IsPositionInside(int _positionCheckX, int _positionCheckY) const
{
	if (_positionCheckX >= rectBlock.x && _positionCheckX <= (rectBlock.x + rectBlock.w) &&
		_positionCheckY >= rectBlock.y && _positionCheckY <= (rectBlock.y + rectBlock.h))
		{
			//std::cout << "punto dentro en altura" << std::endl;
			return true;
		}

	return false;
}


// ResetPosition
// --------------------------
void Block::ResetPosition()
{
	SetPos(initPositionX, initPositionY);
}


