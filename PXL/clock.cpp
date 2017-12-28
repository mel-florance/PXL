#include "clock.h"
#include <SDL2/SDL.h>

Clock::Clock()
{
	m_lastFrame = SDL_GetTicks();
	m_deltaTime = 0;
}

void Clock::update()
{
	m_deltaTime = (SDL_GetTicks() - m_lastFrame) / 1000;
	m_lastFrame = SDL_GetTicks();
}

Clock::~Clock()
{

}