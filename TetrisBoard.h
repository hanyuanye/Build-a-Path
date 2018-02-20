#pragma once
#include <vector>
#include <SDL.h>
#include <stdlib.h>
#include <ctime>
#include "Mino.h"
#include "Constant.h"

enum Mode { build, travel, transistion };
enum TetrisMove { none, rLeft, rRight, mLeft, mRight, mDown, autoDown };
enum PlayerMove { left, right, up };
enum colorName { white, blue, red, green };

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
	TetrisBoard(int height, int width, SDL_Renderer * _ren);
	~TetrisBoard();

	void update(TetrisMove move);
	void render();
	std::vector<std::vector<int>> get_board();
	
private:
	std::vector<std::vector<int>> board;
	SDL_Renderer * ren;
	void render_board();
	void render_tile(color tile_color, int x, int y);
	void generate_mino();
	bool mino_locked();
	bool mino_valid();
	void clear_mino();
	void place_mino();
	void set_mino();
	void replace_mino();
	
	Mino * mino;
};

