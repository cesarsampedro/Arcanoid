#pragma once

#include <SDL.h>

struct Color
{
	int r = 122;
	int g = 122;
	int b = 122;
	int a = 255;
	Color();
	~Color();
	Color(int _r, int _g, int _b, int _a = 255);
};

class Block
{
private:
	Color color;
	int initPositionX = 0;
	int initPositionY = 0;

public:
	int m_posX = 0;
	int m_posY = 0;
	int height = 15;
	int width = 100;
	Block();
	~Block();
	SDL_Rect	rectBlock;
		
	void SetPos(int x, int y);
	void Draw(SDL_Renderer* renderer);
	void SetColor(Color* _color);
	bool IsPositionInside(int _positionCheckX, int _positionCheckY) const;
	void ResetPosition();
};
