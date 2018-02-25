//This class defines all the logic for the build state.
//It updates based on a move and renders accordingly. 
//A lot of helper functions were necessary. 
//
//It also currently has a magic number system that will be replaced with enums
//In the meantime, the numbers are defined:
//-1: The sides of the board. Purple
// 0: Empty. Black
// 1: Locked in minos. Blue
// 2: Controllable mino. Red
// 3: Goal block. Green




#pragma once
#include <vector>
#include <SDL.h>
#include <stdlib.h>
#include <ctime>
#include "Mino.h"
#include "Vec2d.h"
#include "Constant.h"
#include "Obstacle.h"

enum Mode { build, travel, transistion, result_screen_won, result_screen_lost };
enum TetrisMove { none, rLeft, rRight, mLeft, mRight, mDown, autoDown, drop, clear };

extern int xInitial;
extern int yInitial;
extern int tileSize;
extern int lineSize;
extern int TETRIS_MINO_INITX;
extern int TETRIS_MINO_INITY;

struct color {
	int r;
	int g;
	int b;
	color(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}
};



class TetrisBoard
{
public:
	TetrisBoard();
	TetrisBoard(int height, int width, SDL_Renderer * _ren, std::vector<Vec2d> goal_list, std::vector<Vec2d> spike_list);
	~TetrisBoard();

	bool update(TetrisMove move);
	void render();
	std::vector<std::vector<obstacle_type>> get_board();
	
private:
	std::vector<std::vector<obstacle_type>> board;
	SDL_Renderer * ren;
	void render_board();
	void render_tile(color tile_color, int x, int y);
	void generate_mino();
	bool mino_valid();
	void clear_mino();
	void place_mino();
	void set_mino();
	void replace_mino();
	void drop_mino();
	
	Mino * mino;
};

