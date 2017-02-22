#pragma once

#include <SDL.h>
#include "Bar.h"
#include "Timer.h"
#include "Block.h"


class Ball
{

	public:
		Ball( Bar* _bar, SDL_Window* window, enum GameState_t* _gamestate, Block blocks[30]);
		~Ball();
		bool ResetPosition();
		void Update(SDL_Event* e, Bar* bar,enum GameState_t* _gamestate, const Timer* Time);
		void Draw(SDL_Renderer* renderer);
		void OnCollisionEnter(const Timer* Time);
		SDL_Rect rect;

	private:
		SDL_Window       *window;
		Bar              *bar;
		GameState_t		 *gamestate;
		Block			 *blocks;

		const float speedY = 350;
		const float speedX = 300; //35
		float posY = 0;
		float posX = 0;

		int windowWidth  = 0;
		int windowHeight = 0;

		bool isGoingRight = true;
		bool isGoingUp   = true;

		bool firsThrow	  = true;

		int resetPositionX = 0;
		int resetPositionY = 0;
};


