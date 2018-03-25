#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "TetrisBoard.h"
#include "Travel.h"
#include "Constant.h"

extern int TICKS_DOWN_MOVE;
extern int TICKS_MOVE;
extern int TICKS_ROTATE;
extern int TICKS_LOCKED;
extern int TICKS_TETRIS;
extern int PLAYER_WIDTH;
extern int PLAYER_HEIGHT;
extern int PLAYER_HITBOX_WIDTH;
extern int PLAYER_HITBOX_HEIGHT;

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

	void update_ticks(); //Based off 1/60 frame step.

	bool running;

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	Mode mode;

	std::unique_ptr<TetrisBoard> Tetris;
	std::unique_ptr<Travel> travel_mode;
	std::unique_ptr<HitboxManager> hitbox_manager;

	int ticks_last_rotate;
	int ticks_last_move;
	int ticks_last_down_move;
	int ticks_tetris;

	void tetris_input(SDL_Event event);
	void travel_input(SDL_Event event);
	void renderResultScreenWon();
	void renderResultScreenLost();

	TetrisMove tmove;
	PlayerMove pmove;
};

