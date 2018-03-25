#include <iostream>
#include <SDL.h>
#include "Scene.h"
using namespace std;

int main(int argc, char* argv[])
{
	const int FPS = 120;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Scene * scene = new Scene();

	if (scene->init("Simple Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 1000, false)) {

		while (scene->running) {
			frameStart = SDL_GetTicks();

			scene->recieve_input();
			scene->update();
			scene->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}

		}
		scene->clean();

	}
	return 0;
}