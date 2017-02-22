#include "Ball.h"

// Constructor
//----------------------------------------
Ball::Ball( Bar* _bar, SDL_Window* _window, enum GameState_t* _gamestate, Block blocks[30])
{
	rect.h = 15;
	rect.w = 15;
	rect.x = _bar->rect.x + (_bar->rect.w / 2) - (rect.w / 2);	// horizontal over bar
	rect.y = _bar->rect.y - _bar->rect.h - 2;		     		    // vertical over bar
	


	window = _window;

	windowHeight = SDL_GetWindowSurface(window)->h;
	windowWidth  = SDL_GetWindowSurface(window)->w;

	bar = _bar;


	int resetPositionX = rect.x;
	int resetPositionY = rect.y;

	gamestate = _gamestate;

	this->blocks = blocks;
}


// Destructor
//----------------------------------------
Ball::~Ball()
{

}


// UPDATE
//----------------------------------------
void Ball::Update(SDL_Event* e, Bar* bar, enum GameState_t*  _gamestate, const Timer* Time)
{
	switch (*_gamestate)
	{
	case 0:	// Starting
		
		rect.x = bar->rect.x + (bar->rect.w / 2) - (rect.w / 2);
		rect.y = bar->rect.y - bar->rect.h - 2;
		posY = rect.y;
		posX = rect.x;
		rect.y = posY;
		rect.x = posX;
		break;
	
	case 1: // Playing

		
		// First Throw
		if (firsThrow)
		{
			posX += speedX * Time->deltaTime;
			posY -= speedY * Time->deltaTime;
			std::cout << "first throw" << std::endl;
			firsThrow = false;
		}


		OnCollisionEnter(Time);

		switch (isGoingRight)
		{
		case true:
			posX += speedX * Time->deltaTime;
			break;
		case false:
			posX -= speedX * Time->deltaTime;
			break;
		}

		switch (isGoingUp)
		{
			case true:
				posY -= speedY * Time->deltaTime;
				break;
			case false:
				posY += speedY * Time->deltaTime;
				break;
		}
				
		rect.y = posY;
		rect.x = posX;
		break;
	
	case 2: // Dead
		std::cout << "2" << std::endl;
		break;
	}
}


// OnCollisionEnter
//----------------------------------------
void Ball::OnCollisionEnter(const Timer* Time)
{
	// collitions with windows edges
	if (isGoingRight && (int)posX >= (windowWidth - this->rect.w)) // right
	{
		std::cout << "right" << std::endl;
		isGoingRight = false;
	}
	
	if (!isGoingRight && (int)posX <= 0) // left
	{
		std::cout << "left " << std::endl;
		isGoingRight = true;
	}

	if (isGoingUp && (int)posY <= 0) // top
	{
		std::cout << "top" << std::endl;
		isGoingUp = false;
	}

	if (!isGoingUp && (int)posY >= windowHeight - 15) // bottom
	{
		std::cout << "Reset" << std::endl;
		this->ResetPosition();

		isGoingUp = true;
	}

	// check if the ball crash with the player bar.
	if (!isGoingUp && bar->CheckPositionInside(rect.x , posY + rect.h))
	{
		isGoingUp = true;
		std::cout << "barra" << std::endl;
	}

	// check collisions blocks
	for (int i = 0; i < 30; i++)
	{
		// check collision from bottom
		if (isGoingUp && blocks[i].IsPositionInside(rect.x, rect.y))
		{
			blocks[i].rectBlock.x = 1000;
			isGoingUp = false;
		}
		// check collision from top.
		else if ((!isGoingUp && blocks[i].IsPositionInside(rect.x, rect.y + rect.h)))
		{
			blocks[i].rectBlock.x = 1000;
			isGoingUp = true;
		}

		// check collision from right.
		else if ((!isGoingRight && blocks[i].IsPositionInside(rect.x, rect.y)))
		{
			blocks[i].rectBlock.x = 1000;
			isGoingRight = true;
		}

		// check collision from left.
		else if ((isGoingRight && blocks[i].IsPositionInside(rect.x + rect.w, rect.y)))
		{
			blocks[i].rectBlock.x = 1000;
			isGoingRight = false;
		}

	}

	// check for clear board.
	int blocksCounter = 0;
	for (int i = 0; i < 30; i++)
	{
		if (blocks[i].rectBlock.x == 1000)
		{
			blocksCounter++;
		}

		if (blocksCounter >= 30)
		{
			ResetPosition();
		}
	}
}


// DRAW
//----------------------------------------
void Ball::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}


// Reses positions
//----------------------------------------
bool Ball::ResetPosition()
{
	rect.x = resetPositionX;
	rect.y = resetPositionY;

	posY = resetPositionX;
	posX = resetPositionY;

	isGoingRight = true;
	isGoingUp    = true;

	*gamestate = (GameState_t)0;

	// Reset Bar
	bar->ResetPosition();

	// check collisions blocks
	for (int i = 0; i < 30; i++)
	{
		blocks[i].ResetPosition();
	}


	return true;
}

