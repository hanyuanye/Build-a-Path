#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "HitboxManager.h"
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
	void render();
	void createPlayer(const int& boardWidth, const int& boardHeight, const int& playerWidth, const int& playerHeight, const int& hitboxWidth, const int& hitboxHeight);

private: 
	std::shared_ptr<Player> player;
	SDL_Renderer * ren;
};

