//This class defines all controllable sprites. Currently it's only one class but expanding 
//it to an interface style should I want another controllable sprite in the game will be easy.
//The resolve collision function takes in an obstacle with which it has collided with and 
//outputs a result based on the type of obstacle.
//
//For Wall type Obstacles: The sprite stops moving in the direction which caused the collision
//and is set to a position just outside the hitbox of the obstacle.
//
//For Goal type obstacles: The number of goals left decreases. If it hits zero, the game ends. The player wins.
//
//For Spike type obstacles: The number of lives left decreases. If it hits zero, the game ends. The player loses.

#pragma once
#include <memory>
#include "Obstacle.h"
#include "Constant.h"
#include "Vec2d.h"
#include "TextureManager.h"

extern float GRAVITY;

enum state { stand, walk, jump };
enum collision_result { win, lose, no_result };
enum axis { x, y };

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
	Player(Vec2d _min, Vec2d _max, Vec2d pos, int width, int height, SDL_Renderer * _ren);
	Player();
	~Player();
	std::unique_ptr<AABB> hitbox;
	std::unique_ptr<Data> mData;

	void render();
	void updateX();
	void updateY();
	collision_result resolveCollision(std::shared_ptr<Obstacle>& obstacle, axis _axis);
private:
	std::unique_ptr<TextureManager> tex;
	void checkX(std::shared_ptr<Obstacle>& obstacle);
	void checkY(std::shared_ptr<Obstacle>& obstacle);
	
};

