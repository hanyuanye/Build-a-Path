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
	SDL_DestroyRenderer(ren);
}

void Travel::handleInput(PlayerMove pmove)
{
//	cout << pmove << endl;
	switch (pmove) {
	case none_player:
	//	player->mData->mVelocity.set_x(0);
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
						player->mData->mState = jump;
			break;
		case walk:
			player->mData->mVelocity.set_y(PLAYER_VELOCITY_JUMP);
			player->mData->mState = jump;
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

void Travel::render(std::unique_ptr<TetrisBoard>& Tetris)
{
	Tetris->render();
	player->render();
}

void Travel::createPlayer(const int & boardWidth, const int & boardHeight, const int & playerWidth, 
						  const int & playerHeight, const int & hitboxWidth, const int & hitboxHeight)
{
	int minx = boardWidth * (tileSize + 2 * lineSize) + xInitial + (playerWidth - hitboxWidth) / 2;
	int miny = boardHeight * (tileSize + 2 * lineSize) + yInitial + (playerHeight - hitboxHeight) / 2;
	Vec2d min_hitbox = Vec2d(minx, miny);
	Vec2d max_hitbox = Vec2d(minx + hitboxWidth, miny + hitboxHeight);
	Vec2d pos = Vec2d(boardWidth * (tileSize + 2 * lineSize), boardHeight * (tileSize + 2 * lineSize));
	player = std::make_shared<Player>(min_hitbox, max_hitbox, pos, playerWidth, playerHeight, ren);
}


