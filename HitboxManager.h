#pragma once
#include <vector>
#include "Travel.h"

struct AABB {

};
class HitboxManager
{
	friend class Travel;
public:
	HitboxManager(const std::vector<std::vector<int>>& board);
	HitboxManager();
	~HitboxManager();

	void generateAABB(const std::vector<std::vector<int>>& board);
//	void checkCollisions();

private:
	
};

