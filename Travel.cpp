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
		if (player->mData->mState != jump) {
			player->mData->mVelocity.set_x(0);
		}
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

game_state Travel::update(std::unique_ptr<HitboxManager>& hitbox_manager)
{
	player->updateX();
	hitbox_manager->checkCollisionsX(player);
	player->updateY();
	hitbox_manager->checkCollisionsY(player);

	if (hitbox_manager->lives == 0) {
		return game_lost;
	}
	if (hitbox_manager->num_goals == 0) {
		return game_won;
	}
	return game_ongoing;
}

void Travel::updateX()
{
	player->updateX();
}

void Travel::updateY()
{
	player->updateY();
}

void Travel::render(std::unique_ptr<TetrisBoard>& Tetris)
{
	Tetris->render();
	player->render();
}

void Travel::createPlayer(const int & boardWidth, const int & boardHeight, const int & playerWidth, 
						  const int & playerHeight, const int & hitboxWidth, const int & hitboxHeight)
{
	int minx = boardWidth * (TILE_SIZE + 2 * LINE_SIZE) + X_INITIAL + (playerWidth - hitboxWidth) / 2;
	int miny = boardHeight * (TILE_SIZE + 2 * LINE_SIZE) + Y_INITIAL + (playerHeight - hitboxHeight) / 2;
	Vec2d min_hitbox = Vec2d(minx, miny);
	Vec2d max_hitbox = Vec2d(minx + hitboxWidth, miny + hitboxHeight);
	Vec2d pos = Vec2d(boardWidth * (TILE_SIZE + 2 * LINE_SIZE), boardHeight * (TILE_SIZE + 2 * LINE_SIZE));
	player = std::make_shared<Player>(min_hitbox, max_hitbox, pos, playerWidth, playerHeight, ren);
}


