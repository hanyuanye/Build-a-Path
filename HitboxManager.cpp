#include "HitboxManager.h"



HitboxManager::HitboxManager(const std::vector<std::vector<obstacle_type>>& board)
{
	generateAABB(board);
}

HitboxManager::HitboxManager()
{

}


HitboxManager::~HitboxManager()
{

}

//Generates AABB by creating a min Vec2d in top the top left corner of the box
//and a max Vec2d in the bottom right corner of the box
//The min Vec2d has a smaller y and x than max Vec2d
//The difference between these two Vec2ds are the dimensions
void HitboxManager::generateAABB(const std::vector<std::vector<obstacle_type>>& board)
{
	num_goals = 0;
	lives = PLAYER_LIVES;
	for (unsigned i = 0; i < board.size(); i++) {
		for (unsigned j = 0; j < board[0].size(); j++) {
			switch (board[i][j]) {
			case wall:
				addWall(Vec2d(xInitial + i * tileSize, yInitial + j * tileSize), 
						Vec2d(xInitial + (i + 1) * tileSize, yInitial + (j + 1) * tileSize));
				break;
			case empty:
				break;
			case locked_mino:
				addWall(Vec2d(xInitial + i * tileSize, yInitial + j * tileSize),
						Vec2d(xInitial + (i + 1) * tileSize, yInitial + (j + 1) * tileSize));
				break;
			case goal:
				addGoal(Vec2d(xInitial + i * tileSize, yInitial + j * tileSize),
						Vec2d(xInitial + (i + 1) * tileSize, yInitial + (j + 1) * tileSize));
				break;
			case spike:
				addSpike(Vec2d(xInitial + i * tileSize, yInitial + j * tileSize),
						 Vec2d(xInitial + (i + 1) * tileSize, yInitial + (j + 1) * tileSize));
				break;
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

void HitboxManager::addGoal(Vec2d _min, Vec2d _max)
{
	obstacle_list.push_back(std::make_shared<Goal>(_min, _max));
	num_goals++;
}

void HitboxManager::addSpike(Vec2d _min, Vec2d _max)
{
	obstacle_list.push_back(std::make_shared<Spike>(_min, _max));
}

void HitboxManager::checkCollisionsX(std::shared_ptr<Player>& player)
{
	for (int i = 0; i < obstacle_list.size(); i++) {
		if (checkAABB(obstacle_list[i]->obstacle_hitbox, player->hitbox)) {
			updatePlayerStatus(player->resolveCollision(obstacle_list[i], x), i);
		}
	}
}

void HitboxManager::checkCollisionsY(std::shared_ptr<Player>& player)
{
	for (int i = 0; i < obstacle_list.size(); i++) {
		if (checkAABB(obstacle_list[i]->obstacle_hitbox, player->hitbox)) {
			updatePlayerStatus(player->resolveCollision(obstacle_list[i], y), i);
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

void HitboxManager::updatePlayerStatus(collision_result result, int i)
{
	switch (result) {
	case no_result:
		break;
	case win:
		num_goals--;
		obstacle_list.erase(obstacle_list.begin() + i);
		break;
	case lose:
		lives--;
		obstacle_list.erase(obstacle_list.begin() + i);
		break;
	default:
		break;
	}
}
