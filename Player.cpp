#include "Player.h"



Player::Player(Vec2d _min, Vec2d _max, int width, int height, SDL_Renderer * _ren)
{
	hitbox = std::make_unique<AABB>(_min, _max);
	tex = std::make_unique<TextureManager>(_ren, "Assets/player.png", 255, 255, 255, width, height);
}

Player::Player()
{
}


Player::~Player()
{
}

void Player::render()
{
	tex->render(mData->mPosition);
}

void Player::update()
{
	mData->mPosition += mData->mVelocity;
	mData->mVelocity += mData->mAcceleration;
}

void Player::resolveCollision(std::shared_ptr<Obstacle>& obstacle)
{
	switch (obstacle->type) {

	case wall:
		switch (mData->mState) {
		case walk:
			if (obstacle->obstacle_hitbox->max.get_x() > hitbox->min.get_x() &&
				obstacle->obstacle_hitbox->min.get_x() < hitbox->min.get_x() &&
				mData->mVelocity.get_x() < 0) {
				mData->mVelocity.set_x(0);
				mData->mState = stand;
			}
			else
				if (obstacle->obstacle_hitbox->min.get_x() < hitbox->max.get_x() &&
					obstacle->obstacle_hitbox->max.get_x() > hitbox->max.get_x() &&
					mData->mVelocity.get_x() > 0) {
					mData->mVelocity.set_x(0);
					mData->mState = stand;
				}
			break;
		case jump:
			if (obstacle->obstacle_hitbox->min.get_y() < hitbox->max.get_y()) {
				mData->mVelocity.set_y(0);
			}
			else {
				mData->mVelocity.set_y(0);
				mData->mAcceleration.set_y(GRAVITY);
				mData->mState = walk;
			}
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}
