#include "Constant.h"
#pragma once

int xInitial = 0;
int yInitial = 0;

int tileSize = 30;
int lineSize = 1;

int ticks_down_move = 60;
int ticks_move = 8;
int ticks_rotate= 20;
int TICKS_TETRIS = 120 * 60; //120 is the number of ticks, change the right value to change the seconds

int TETRIS_MINO_INITX = 1;
int TETRIS_MINO_INITY = 0;

int PLAYER_VELOCITY_X = 1;
int PLAYER_VELOCITY_JUMP = -4.5;

float GRAVITY = 10.0 / 120.0;

int PLAYER_HEIGHT = 25;
int PLAYER_WIDTH = 25;
int PLAYER_HITBOX_HEIGHT = 20;
int PLAYER_HITBOX_WIDTH = 15;

int PLAYER_LIVES = 1;

//mPieces assumes a 5x5 grid. The rotation piece for each mino will be in the centre position at (2, 2). 
//Then, we can figure out where all the actual blocks are for each rotation by adding it's position relative
//to the 5x5 grid with it's x and y positions which would always be the (0, 0) spot for the grid. 

int mPieces[7 /*kind */][4 /* rotation */][4/* horizontal blocks */][2 /* vertical blocks */] =
{
	// Square
	{
		{
			{ 2, 2 },
			{ 2, 3 },
			{ 3, 2 },
			{ 3, 3 }
		},
			{
				{ 2, 2 },
				{ 2, 3 },
				{ 3, 2 },
				{ 3, 3 }
			},
			{
				{ 2, 2 },
				{ 2, 3 },
				{ 3, 2 },
				{ 3, 3 }
			},
			{
				{ 2, 2 },
				{ 2, 3 },
				{ 3, 2 },
				{ 3, 3 }
			}
	},

	// I
		{
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 4, 2 },
			},
			{
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 },
				{ 2, 4 },
			},
			{
				{ 0, 2 },
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 }
			},
			{
				{ 2, 0 },
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 }
			}
		},
	// L
		{
			{
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 },
				{ 3, 3 }
			},
			{
				{ 1, 3 },
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 }
			},
			{
				{ 1, 1 },
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 }
			},
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 3, 1 }
			}
		},
	// L Mirrored
		{
			{
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 },
				{ 1, 3 }
			},
			{
				{ 1, 1 },
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 }
			},
			{
				{ 3, 1 },
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 }
			},
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 3, 3 }
			}
		},
	// N
		{
			{
				{ 3, 1 },
				{ 3, 2 },
				{ 2, 2 },
				{ 2, 3 }
			},
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 2, 3 },
				{ 3, 3 }
			},
			{
				{ 1, 3 },
				{ 1, 2 },
				{ 2, 2 },
				{ 2, 1 }
			},
			{
				{ 1, 1 },
				{ 2, 1 },
				{ 2, 2 },
				{ 3, 2 }
			}
		},
	// N mirrored
		{
			{
				{ 2, 1 },
				{ 2, 2 },
				{ 3, 2 },
				{ 3, 3 }
			},
			{
				{ 1, 3 },
				{ 2, 3 },
				{ 2, 2 },
				{ 3, 2 }
			},
			{
				{ 1, 1 },
				{ 1, 2 },
				{ 2, 2 },
				{ 2, 3 }
			},
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 2, 1 },
				{ 3, 1 }
			}
		},
	// T
		{
			{
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 },
				{ 3, 2 }
			},
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 2, 3 }
			},
			{
				{ 2, 1 },
				{ 2, 2 },
				{ 2, 3 },
				{ 1, 2 }
			},
			{
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 2, 1 }
			}
		}
};