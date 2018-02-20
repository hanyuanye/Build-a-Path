#pragma once
#include <vector>
#include <algorithm>
#include "Constant.h"
extern int mPieces[7][4][4][2];
extern int TETRIS_MINO_INITX;
extern int TETRIS_MINO_INITY;

class Mino
{
public:
	Mino();
	Mino(int piece);
	~Mino();
	std::vector<std::vector<int>> get_tiles();
	int mOrientation;
	int x;
	int y;
	int mPiece;
private:

};

