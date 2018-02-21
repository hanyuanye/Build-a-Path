//This class defines all controllable sprites. Currently it's only one class but expanding 
//it to an interface style should I want another controllable sprite in the game will be easy.
//Since I do not expect this class to ever have relevant collisions with anything other than obstacles,
//the resolveCollision function is hardcoded to only accept obstacles. Note: only Wall Collision 
//functionality is implemented so far but that will change when spikes and others will be implemented.

#pragma once
#include <memory>
#include "Obstacle.h"
#include "Constant.h"
#include "Vec2d.h"
#include "TextureManager.h"

extern int GRAVITY;

enum state { stand, walk, jump };

struct Data {
	Vec2d mPosition;
	Vec2d mVelocity;
	Vec2d mAcceleration;
	state mState;
	Data() : mPosition(Vec2d()), mVelocity(Vec2d()), mAcceleration(Vec2d(0, GRAVITY)), mState(walk) {}
	Data(Vec2d position, Vec2d velocity, state state) : mPosition(position), mVelocity(velocity), mAcceleration(Vec2d(0, GRAVITY)), mState(state) {}

};


class Player
{
public:
	Player(Vec2d _min, Vec2d _max, int width, int height, SDL_Renderer * _ren);
	Player();
	~Player();
	std::unique_ptr<AABB> hitbox;
	std::unique_ptr<Data> mData;

	void render();
	void update();
	void resolveCollision(std::shared_ptr<Obstacle>& obstacle);
private:
	std::unique_ptr<TextureManager> tex;
	
};

