#include "Player.h"



Player::Player(Vec2d _min, Vec2d _max, Vec2d pos, int width, int height, SDL_Renderer * _ren)
{
	mData = std::make_unique<Data>(pos, Vec2d(), jump);
	hitbox = std::make_unique<AABB>(pos, pos + Vec2d(width, height));
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

void Player::updateX()
{
	mData->mPosition.set_x(mData->mVelocity.get_x() + mData->mPosition.get_x());
	mData->mVelocity.set_x(mData->mVelocity.get_x() + mData->mAcceleration.get_x());
	Vec2d diff = hitbox->max - hitbox->min;
	hitbox->min = mData->mPosition;
	hitbox->max = hitbox->min + diff;
}

void Player::updateY()
{
	mData->mPosition.set_y(mData->mVelocity.get_y() + mData->mPosition.get_y());
	mData->mVelocity.set_y(mData->mVelocity.get_y() + mData->mAcceleration.get_y());
	Vec2d diff = hitbox->max - hitbox->min;
	hitbox->min = mData->mPosition;
	hitbox->max = hitbox->min + diff;
}

void Player::resolveCollision(std::shared_ptr<Obstacle>& obstacle, axis _axis)
{
	switch (obstacle->type) {

	case wall:
		switch (_axis) {
		case x:
			checkX(obstacle);
			break;
		case y:
			checkY(obstacle);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Player::checkX(std::shared_ptr<Obstacle>& obstacle)
{
	mData->mVelocity.set_x(0);
	if (obstacle->obstacle_hitbox->max.get_x() > hitbox->max.get_x()) {
		int width = hitbox->max.get_x() - hitbox->min.get_x();
		mData->mPosition.set_x(obstacle->obstacle_hitbox->min.get_x() - width);
	}
	else {
		mData->mPosition.set_x(obstacle->obstacle_hitbox->max.get_x());
	}
}

void Player::checkY(std::shared_ptr<Obstacle>& obstacle)
{
	if (obstacle->obstacle_hitbox->min.get_y() > hitbox->min.get_y()) {
		mData->mState = stand;
	} 
	if (mData->mVelocity.get_y() >= 0) {
		int height = hitbox->max.get_y() - hitbox->min.get_y();
		mData->mPosition.set_y(obstacle->obstacle_hitbox->min.get_y() - height);
	}
	else {
		mData->mPosition.set_y(obstacle->obstacle_hitbox->max.get_y());
	}
	mData->mVelocity.set_y(0);
}
