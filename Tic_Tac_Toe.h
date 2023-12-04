#pragma once

int board[3][3] =
{
{-1, -1, -1},
  {-1, -1, -1},
  {-1, -1, -1}
};

/*
  //0
{-1, -1, -1},
  {-1, -1, -1},
  {-1, -1, -1}

  //1
{1, -1, 0},
  {0, 1, 1},
  {-1, 1, 0}

  //2
   {-1, 0, 0},
  {0, 1, 1},
  {1, -1, -1}
   
   //2.1 (full)
  {-1, -1, 0},
  {0, 1, 1},
  {1, -1, -1}

   //3(tie)
   {-1, 1, 0},
  {0, 1, 1},
  {1, 0, -1}


*/

int emuBoard[3][3] =
{
	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 }
};

int bestBoard[3][3] =
{
	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 }
};


int
	
	ComputerXChoice = -1,
	ComputerYChoice = -1,
	step, //once we check how many step, we will know how long until stop
	tmpscore,
	score; //value each time go 

void replicatedBoard(int from[3][3], int to[3][3]);


struct boardIndex
{
	int x;
	int y;
};

struct storageStep
{
	struct boardIndex last;
	struct boardIndex now;
	int step;
	int score;
};

struct storageStep inputStep(
	struct boardIndex last,
	struct boardIndex now,
	int step,
	int score);

void BoardShowing(int newboard[3][3]);

int isWin(int X, bool isXsame, int Y, bool isYsame, bool isDiagonals, int checkboard[3][3]);

int checkState(int checkboard[3][3]);

int BoardCheck(int boardCount, int checkboard[3][3]);

void BoardChanging(boardIndex index, int checked);

void playerChoice();

void computerChoice();

int Minimax(int currentstep, int nextBoard[3][3], bool isComputerTurn, int alpha, int beta);

int CountBoard();

//x: min; O: max