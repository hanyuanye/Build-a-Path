#pragma once
#include <memory>
#include "Vec2d.h"


enum obstacle_type { wall, goal };
struct AABB {
	Vec2d min;
	Vec2d max;
	AABB() : min(Vec2d()), max(Vec2d()) {}
	AABB(Vec2d _min, Vec2d _max) : min(_min), max(_max) {}
};

class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	std::unique_ptr<AABB> obstacle_hitbox;
	obstacle_type type;

};


class Wall : public Obstacle
{
public:
	Wall(Vec2d _min, Vec2d _max);
private:

};

class Goal : public Obstacle
{
public:
	Goal(Vec2d _min, Vec2d _max);
};
