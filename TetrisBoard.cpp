#include "TetrisBoard.h"



TetrisBoard::TetrisBoard()
{
}

TetrisBoard::TetrisBoard(int height, int width, SDL_Renderer * _ren, std::vector<Vec2d> goal_list, std::vector<Vec2d> spike_list)
{
	srand(time(NULL));
	ren = _ren;
	board.resize(height);
	for (auto &i : board) {
		i.resize(width, empty);
	}
	for (unsigned i = 0; i < board.size(); i++) {
		board[i][0]= wall;
		board[i][board[0].size() - 1] = wall;
	}
	for (unsigned j = 0; j < board[0].size(); j++) {
		board[0][j] = wall;
		board[board.size() - 1][j] = wall;
	}
	generate_mino();
	for (int i = 0; i < goal_list.size(); i++) {
		board[goal_list[i].get_x()][goal_list[i].get_y()] = goal;
	}

	for (int i = 0; i < spike_list.size(); i++) {
		board[spike_list[i].get_x()][spike_list[i].get_y()] = spike;
	}
}


TetrisBoard::~TetrisBoard()
{
	SDL_DestroyRenderer(ren);
}

bool TetrisBoard::update(TetrisMove move)
{
	clear_mino();
	switch (move) {
	// 4 represents the number of possible mino orientations
	// The numbers should rotate from 0 -> 3 so an orientation of 0 going down will become 3 not -1
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
		return true;
		break;
	default:
		break;
	}
	if (mino == NULL) {
		return false;
	}
	place_mino();
	return true;
}

void TetrisBoard::render()
{
	render_board();
}

std::vector<std::vector<obstacle_type>> TetrisBoard::get_board()
{
	return board;
}

void TetrisBoard::generate_mino()
{
	for (unsigned i = 1; i < 5; i++) {
		for (unsigned j = 1; j < 5; j++) {
			if (board[TETRIS_MINO_INITX + i][TETRIS_MINO_INITY + j] != empty) {
				mino = NULL;
 				return;
			}
		}
	}

	int piece = rand() % 7; //7 is equal to the number of minos
	mino = new Mino(piece);
}

bool TetrisBoard::mino_valid()
{
	std::vector<std::vector<int>> tiles = mino->get_tiles();
	for (unsigned i = 0; i < tiles.size(); i++) {
		if (board[tiles[i][0]][tiles[i][1]] != empty) {
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
				if (board[i + mino->x][j + mino->y] == moving_mino) {
					board[i + mino->x][j + mino->y] = empty;
				}
			}
		}
	}
}

void TetrisBoard::place_mino()
{
	std::vector<std::vector<int>> tiles = mino->get_tiles();
	for (unsigned i = 0; i < tiles.size(); i++) {
		board[tiles[i][0]][tiles[i][1]] = moving_mino;
	}
}

void TetrisBoard::set_mino()
{
	std::vector<std::vector<int>> tiles = mino->get_tiles();
	for (unsigned i = 0; i < tiles.size(); i++) {
		board[tiles[i][0]][tiles[i][1]] = locked_mino;
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
			case wall:
				render_tile(color(128, 0 ,128), i, j); //purple
				break;
			case empty:
				render_tile(color(0, 0, 0), i, j); //black
				break;
			case locked_mino:
				render_tile(color(0, 0, 204), i, j); //blue
				break;
			case moving_mino:
				render_tile(color(204, 0, 0), i, j); //red
				break;
			case goal:
				render_tile(color(0, 204, 0), i, j); //green
				break;
			case spike:
				render_tile(color(47, 79, 79), i, j); //dark grey
				break;
			}
		}
	}
}

void TetrisBoard::render_tile(color tile_color, int x, int y)
{
	int xpos = X_INITIAL + x * TILE_SIZE - LINE_SIZE;
	int ypos = Y_INITIAL + y * TILE_SIZE - LINE_SIZE;

	SDL_Rect r{ xpos, ypos, TILE_SIZE - LINE_SIZE * 2, TILE_SIZE - LINE_SIZE * 2 };
	SDL_SetRenderDrawColor(ren, tile_color.r, tile_color.g, tile_color.b, 255);
	SDL_RenderFillRect(ren, &r);
}

