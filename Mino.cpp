#include "Mino.h"

int counter = 0;
Mino::Mino()
{

}

Mino::Mino(int piece)
{
	mPiece = piece;
	mOrientation = 0;
	y = TETRIS_MINO_INITY;
	x = TETRIS_MINO_INITX;
}

Mino::~Mino()
{

}

std::vector<std::vector<int>> Mino::get_tiles()
{
	std::vector<std::vector<int>> v;
	v.resize(4);
	for (unsigned i = 0; i < v.size(); i++) {
		v[i].resize(2);
	}
	for (int i = 0; i < 4; i++) {
/*		counter++;
		cout << counter << endl;
		cout << mPieces[mPiece][mOrientation][i][0] + x << endl;*/ //TODO: Fix seg fault
		v[i][0] = mPieces[mPiece][mOrientation][i][0] + x;
		v[i][1] = mPieces[mPiece][mOrientation][i][1] + y;
	}
	return v;
}
