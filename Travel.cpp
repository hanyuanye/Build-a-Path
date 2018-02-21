#include "Travel.h"
#include "Player.h"



Travel::Travel()
{
}

Travel::Travel(SDL_Renderer * _ren)
{
	ren = _ren;
}


Travel::~Travel()
{
}

void Travel::handleInput(PlayerMove pmove)
{
	switch (pmove) {
	case none_player:
		player->mData->mVelocity.set_x(0);
		break;
	case left_player:
		player->mData->mVelocity.set_x(-PLAYER_VELOCITY_X);
		break;
	case right_player:
		player->mData->mVelocity.set_x(PLAYER_VELOCITY_X);
		break;
	case up_player:
		switch (player->mData->mState) {
		case stand:
			player->mData->mVelocity.set_y(PLAYER_VELOCITY_JUMP);
			break;
		case walk:
			player->mData->mVelocity.set_y(PLAYER_VELOCITY_JUMP);
			break;
		case jump:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Travel::update()
{
	player->update();
}

void Travel::render()
{
	player->render();
}

void Travel::createPlayer(const int & boardWidth, const int & boardHeight, const int & playerWidth, 
						  const int & playerHeight, const int & hitboxWidth, const int & hitboxHeight)
{
	int minx = boardWidth * (tileSize + 2 * lineSize) + xInitial + (playerWidth - hitboxWidth) / 2;
	int miny = boardHeight * (tileSize + 2 * lineSize) + yInitial + (playerHeight - hitboxHeight) / 2;
	Vec2d min = Vec2d(minx, miny);
	Vec2d max = Vec2d(minx + hitboxWidth, miny + hitboxHeight);
	player = std::make_shared<Player>(min, max, playerWidth, playerHeight, ren);
}


