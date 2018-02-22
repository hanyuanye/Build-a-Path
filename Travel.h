#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "HitboxManager.h"
#include "TetrisBoard.h"
#include "Player.h"

enum PlayerMove { none_player, left_player, right_player, up_player };

extern int PLAYER_VELOCITY_X;
extern int PLAYER_VELOCITY_JUMP;
extern int tileSize;
extern int lineSize;
extern int xInitial;

class Travel
{
public:
	Travel();
	Travel(SDL_Renderer * _ren);
	~Travel();

	void handleInput(PlayerMove pmove);
	void update();
	void render(std::unique_ptr<TetrisBoard>& Tetris);
	void createPlayer(const int& boardWidth, const int& boardHeight, const int& playerWidth, const int& playerHeight, const int& hitboxWidth, const int& hitboxHeight);
	std::shared_ptr<Player> player;

private: 
	SDL_Renderer * ren;
};

