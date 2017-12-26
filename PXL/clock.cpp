#include "clock.h"
#include <iostream>
#include <SDL2/SDL.h>

Clock::Clock()
{
	m_lastFrame = SDL_GetTicks();
	m_deltaTime = 0;
}

Clock::~Clock()
{

}
