#include "TetrisBoard.h"



TetrisBoard::TetrisBoard()
{
}

TetrisBoard::TetrisBoard(int height, int width, SDL_Renderer * _ren)
{
	srand(time(NULL));
	ren = _ren;
	board.resize(height);
	for (auto &i : board) {
		i.resize(width, 0);
	}
	for (unsigned i = 0; i < board.size(); i++) {
		board[i][0]= -1;
		board[i][board[0].size() - 1] = -1;
	}
	for (unsigned j = 0; j < board[0].size(); j++) {
		board[0][j] = -1;
		board[board.size() - 1][j] = -1;
	}
	generate_mino();
}


TetrisBoard::~TetrisBoard()
{
	SDL_DestroyRenderer(ren);
}

void TetrisBoard::update(TetrisMove move)
{
	clear_mino();
	switch (move) {
	case none:
		break;
	case rLeft:
		mino->mOrientation--;
		if (mino->mOrientation < 0) {
			mino->mOrientation = 3;
		}
		if (!mino_valid()) {
			mino->mOrientation = (mino->mOrientation + 1) % 4;
		}
		break;
	case rRight:
		mino->mOrientation = (mino->mOrientation + 1) % 4;
		if (!mino_valid()) {
			mino->mOrientation--;
			if (mino->mOrientation < 0) {
				mino->mOrientation = 3;
			}
		}
		break;
	case mLeft:
		mino->x--;
		if (!mino_valid()) {
			mino->x++;
		}
		break;
	case mRight:
		mino->x++;
		if (!mino_valid()) {
			mino->x--;
		}
		break;
	case mDown:
		mino->y++;
		if (!mino_valid()) {
			mino->y--;
		}
	case autoDown:
		mino->y++;
		if (!mino_valid()) {
			mino->y--;
			replace_mino();
		}
		break;
	case drop:
		drop_mino();
		replace_mino();
		break;
	case clear:
		clear_mino();
		delete mino;
		return;
		break;
	default:
		break;
	}
	place_mino();
}

void TetrisBoard::render()
{
	render_board();
}

std::vector<std::vector<int>> TetrisBoard::get_board()
{
	return board;
}

void TetrisBoard::generate_mino()
{
	if (board[TETRIS_MINO_INITX + 2][TETRIS_MINO_INITY + 2] != 0) {
		return;
	}
	int piece = rand() % 7;
	mino = new Mino(piece);
}

bool TetrisBoard::mino_valid()
{
	std::vector<std::vector<int>> tiles = mino->get_tiles();
	for (unsigned i = 0; i < tiles.size(); i++) {
		if (board[tiles[i][0]][tiles[i][1]] != 0) {
			return false;
		}
	}
	return true;
}

void TetrisBoard::clear_mino()
{
	for (unsigned i = 0; i < 5; i++) {
		for (unsigned j = 0; j < 5; j++) {
			if (i + mino->x < board.size() && j + mino->y < board[0].size()) {
				if (board[i + mino->x][j + mino->y] == 2) {
					board[i + mino->x][j + mino->y] = 0;
				}
			}
		}
	}
}

void TetrisBoard::place_mino()
{
	std::vector<std::vector<int>> tiles = mino->get_tiles();
	for (unsigned i = 0; i < tiles.size(); i++) {
		board[tiles[i][0]][tiles[i][1]] = 2;
	}
}

void TetrisBoard::set_mino()
{
	std::vector<std::vector<int>> tiles = mino->get_tiles();
	for (unsigned i = 0; i < tiles.size(); i++) {
		board[tiles[i][0]][tiles[i][1]] = 1;
	}
}

void TetrisBoard::replace_mino()
{
	set_mino();
	delete mino;
	generate_mino();
}

void TetrisBoard::drop_mino()
{
	while (mino_valid()) {
		mino->y++;
	}
	mino->y--;
}

void TetrisBoard::render_board()
{
	for (unsigned i = 0; i < board.size(); i++) {
		for (unsigned j = 0; j < board[0].size(); j++) {
			switch (board[i][j]) {
			case -1:
				render_tile(color(128, 0 ,128), i, j);
				break;
			case 0:
				render_tile(color(0, 0, 0), i, j);
				break;
			case 1:
				render_tile(color(0, 0, 204), i, j);
				break;
			case 2:
				render_tile(color(204, 0, 0), i, j);
				break;
			}
		}
	}
}

void TetrisBoard::render_tile(color tile_color, int x, int y)
{
	int xpos = xInitial + x * tileSize - lineSize;
	int ypos = yInitial + y * tileSize - lineSize;

	SDL_Rect r{ xpos, ypos, tileSize - lineSize * 2, tileSize - lineSize * 2 };
	SDL_SetRenderDrawColor(ren, tile_color.r, tile_color.g, tile_color.b, 255);
	SDL_RenderFillRect(ren, &r);
}

