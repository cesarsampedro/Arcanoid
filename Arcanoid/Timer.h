#pragma once

class Timer
{
	public:
		float GetDeltaTime()
		{
			previous_time = current_time;
			current_time  = SDL_GetTicks();
			deltaTime	  = (current_time - previous_time) / 1000.0f;
			return deltaTime;
		}
	
	private:

		uint32_t current_time  = 0;
		uint32_t previous_time = 0;

	public:

		float  deltaTime     = 0;
};

// ver framerate
// 	std::cout << (deltaTime / 60) * 1000 << std::endl;