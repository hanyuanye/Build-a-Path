#pragma once
#include <SDL.h>
#include "TetrisBoard.h"

extern int ticks_down_move;
extern int ticks_move;
extern int ticks_rotate;
extern int TICKS_LOCKED;
extern int TICKS_TETRIS;

class Scene
{
public:
	Scene();
	~Scene();
	bool init(const char*, int, int, int, int, bool);
	void recieve_input();
	void update();
	void render();
	void clean();

	void update_ticks();

	bool running;

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	Mode mode;

	TetrisBoard * Tetris;
	TetrisMove tmove;

	int ticks_last_rotate;
	int ticks_last_move;
	int ticks_last_down_move;
	int ticks_tetris;

	void tetris_input(SDL_Event event);
};

