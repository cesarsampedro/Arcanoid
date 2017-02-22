#define SDL_MAIN_HANDLED 

#include <SDL.h>
#include <iostream>
#include "Timer.h"
#include "Bar.h"
#include "Ball.h"
#include "Block.h"

bool Running = true;

enum GameState_t
{
	Starting,
	Playing,
	Dead
};


// HandleEvents
//----------------------------------------
int HandleEvents(SDL_Event* e, GameState_t* _gamestate, const Uint8* keyboard_state_array)
{
	if (e->type == SDL_KEYDOWN)
	{
		if (keyboard_state_array[SDL_SCANCODE_ESCAPE])
		{
			Running = false;
			return 0;
		}

		else if (keyboard_state_array[SDL_SCANCODE_SPACE])
		{

			if (*_gamestate == GameState_t::Starting)
			{
				*_gamestate = GameState_t::Playing;
			}
		}
	}

	if (e->type == SDL_QUIT)
	{
		Running = false;
		return 0;
	}
	
	return 1;
}


// DoRender
//----------------------------------------
void DoRender(SDL_Renderer* renderer, Bar* bar, Ball* ball, Block block[])
{
	bar->Draw(renderer);
	ball->Draw(renderer);

	for (int i = 0; i < 30; i++)
	{
		block[i].Draw(renderer);
	}
}


// CreatingBlocks
//----------------------------------------
void CreateBlocks(const int WINDOW_WIDTH,Block block[30])
{
	const int spaceBetweenPiezes = 3;
	int lastblock = 0;
	int columns = 0;
	int countPiezes = 0;
	int centerPiecesSize = 0;

	centerPiecesSize = (WINDOW_WIDTH - ((100 + spaceBetweenPiezes) * 5)) / 2;

	for (int i = 0; i < 30; i++)
	{
		if (countPiezes == 5)
		{
			countPiezes = 0;
			lastblock = 0;
			columns += 1;
		}

		block[i].SetPos(centerPiecesSize + lastblock, 100 + (columns * (15 + spaceBetweenPiezes)));

		switch (columns)
		{
		case 0:
			block[i].SetColor(new Color(255, 0, 122));   // adding  color
			break;
		case 1:
			block[i].SetColor(new Color(222, 232, 122)); // adding  color
			break;
		case 2:
			block[i].SetColor(new Color(22, 122, 221));  // adding  color
			break;
		case 3:
			block[i].SetColor(new Color(33, 133, 60));   // adding  color
			break;
		case 4:
			block[i].SetColor(new Color(177, 40, 120));  // adding  color
			break;
		case 5:
			block[i].SetColor(new Color(111, 99, 220));  // adding  color
			break;
		case 6:
			block[i].SetColor(new Color(33, 122, 55));   // adding  color
			break;
		}

		countPiezes += 1;
		lastblock += spaceBetweenPiezes + block[i].width;
	}
}


// MAIN
//----------------------------------------
int main(int, int, char*, int)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	const int WINDOW_WIDTH  = 700;
	const int WINDOW_HEIGHT = 800;

	// Kesys multiVariable
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);


	SDL_Window*   window   = SDL_CreateWindow("Arcanoid", 500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event	  e;

	GameState_t gameState = Starting;

	Timer Time;
	Bar   bar(WINDOW_WIDTH, WINDOW_HEIGHT);
	Block block[30];
	Ball  ball(&bar, window, &gameState, block);
	
	CreateBlocks(WINDOW_WIDTH, block);


	// MAIN LOOP
	while (Running)
	{
		//Update Timer
		Time.GetDeltaTime();

		//Input.
		SDL_PollEvent(&e);
		Running = HandleEvents(&e, &gameState, keyboard_state_array);
		
		//Update
		bar.Update(&e, &Time, keyboard_state_array);
		ball.Update(&e, &bar, &gameState, &Time);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Render
		DoRender(renderer, &bar, &ball, block);
		SDL_RenderPresent(renderer);
	}
	return 0;
}