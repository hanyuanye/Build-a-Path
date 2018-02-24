#include "HitboxManager.h"



HitboxManager::HitboxManager(const std::vector<std::vector<int>>& board)
{
	generateAABB(board);
}

HitboxManager::HitboxManager()
{

}


HitboxManager::~HitboxManager()
{

}

void HitboxManager::generateAABB(const std::vector<std::vector<int>>& board)
{
	for (unsigned i = 0; i < board.size(); i++) {
		for (unsigned j = 0; j < board[0].size(); j++) {
			switch (board[i][j]) {
			case -1:
				addWall(Vec2d(xInitial + (i) * (tileSize + lineSize*0), yInitial + (j) * (tileSize + lineSize*0)), 
						Vec2d(xInitial + (i + 1) * (tileSize + lineSize*0), yInitial + (j + 1) * (tileSize + lineSize*0)));
				break;
			case 0:
				break;
			case 1:
				addWall(Vec2d(xInitial + i * (tileSize + 2 * lineSize*0), yInitial + j * (tileSize + 2 * lineSize*0)),
						Vec2d(xInitial + (i + 1) * (tileSize + 2 * lineSize*0), yInitial + (j + 1) * (tileSize + 2 * lineSize*0)));
				break;
/*			case 3:
				addSpike(Vec2d(xInitial + i * (tileSize + 2 * lineSize), yInitial + j * (tileSize + 2 * lineSize)),
						 Vec2d(xInitial + (i + 1) * (tileSize + 2 * lineSize), yInitial + (j + 1) * (tileSize + 2 * lineSize)));
				break;*/
			default:
				break;
			}
		}
	}
}

void HitboxManager::addWall(Vec2d _min, Vec2d _max)
{
	obstacle_list.push_back(std::make_shared<Wall>(_min, _max));
}

void HitboxManager::checkCollisionsX(std::shared_ptr<Player>& player)
{
	for (auto& i : obstacle_list) {
		if (checkAABB(i->obstacle_hitbox, player->hitbox)) {
			player->resolveCollision(i, x);
		}
	}
}

void HitboxManager::checkCollisionsY(std::shared_ptr<Player>& player)
{
	for (auto& i : obstacle_list) {
		if (checkAABB(i->obstacle_hitbox, player->hitbox)) {
			player->resolveCollision(i, y);
		}
	}
}

bool HitboxManager::checkAABB(std::unique_ptr<AABB>& A, std::unique_ptr<AABB>& B)
{
	if (A->max.get_x() > B->min.get_x() &&
		A->min.get_x() < B->max.get_x() &&
		A->max.get_y() > B->min.get_y() &&
		A->min.get_y() < B->max.get_y()) {
		return true;
	}
	return false;
}
