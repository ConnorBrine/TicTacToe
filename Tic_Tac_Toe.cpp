#include <iostream>
#include <vector>
#include "Tic_Tac_Toe.h"

using namespace std;

vector <int> possiblePos;

string isChecked(int a, int b, int newboard[3][3])
{ //get data in board
	if (newboard[a][b] == -1) return " ";
	else if (newboard[a][b] == 0) return "o";
	return "x"; 
}

struct storageStep inputStep(
	struct boardIndex last,
	struct boardIndex now,
	int step,
	int score)
{
	struct storageStep storeStep;
	storeStep.last = last;
	storeStep.now = now;
	storeStep.score = score;
	storeStep.step = step;
	return storeStep;
}

void replicatedBoard(int from[3][3], int to[3][3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			to[i][j] = from[i][j];
		}
	}
	return;
}

void BoardShowing(int newboard[3][3])
{
	cout << "-------" << endl;
	for (int i = 0; i <= 2; i++) {
		cout << "|";
		for (int j = 0; j <= 2; j++) {
			cout << isChecked(i, j , newboard) << "|";
		}
		cout << endl;
	}
	cout << "-------" << endl;
}

int isWin(int X, bool isXsame, int Y, bool isYsame, bool isDiagonals, int checkboard[3][3])
{
	struct boardIndex numCount { 2, 2 };
	int value = checkboard[X][Y];
	
	
	if (value == -1)
	{ //we need check if first value is checked or not (when -1 is not checked)
		return -2;
	}

	if (isDiagonals)
	{ //we dont need check Y as Y is not change during check all value is true
		if (X == 2)
		{
			numCount.x = 0;
		}
		int i = X, j = Y;
		while (i <= 2 && i >= 0 || j <= 2 && j >= 0)
		{
			//cout << "Test (" << i << ", " << j << ")\n";
			if (value != checkboard[i][j])
			{
				return -2;
			}
			if (numCount.x == 0) i--;
			else i++;
			j++;
		}
	}

	else 
	{
		if (isXsame)
		{
			numCount.x = X;
		}
		if (isYsame)
		{
			numCount.y = Y;
		}

		for (int i = X; i <= numCount.x; i++) {
			for (int j = Y; j <= numCount.y; j++) {
				//cout << "Test (" << i << ", " << j << ") = " << checkboard[i][j] <<"\n";
				if (checkboard[i][j] == -1 || value != checkboard[i][j])
				{
					return -2;
				}
			}
		}
	}
	//if have number, return value
	
	return value;
}

int checkState(int checkboard[3][3])
{
	int tmp;
	for (int i = 0; i < 3; i++)
	{
		tmp = isWin(0, false, i, true, false, checkboard);
		if(tmp != -2) 
			return tmp;
	}
	for (int i = 0; i < 3; i++) 
	{
		tmp = isWin(i, true, 0, false, false, checkboard);
		if (tmp != -2) 
			return tmp;
	}
	if(tmp == -2)
	{
		tmp = isWin(0, false, 0, false, true, checkboard);
		if (tmp != -2) 
			return tmp;
		tmp = isWin(2, false, 0, false, true, checkboard);
		if (tmp != -2) 
			return tmp;
	}
	return -2;
}

int BoardCheck(int boardCount, int checkboard[3][3])
{

	//terminal case for win/lose game 
	tmpscore = checkState(checkboard);

	//forgot to sync right number, so instead that description that number
	//if 0 => return -1 (O win)
	//if 1 => return 1 (X win)
	if (tmpscore == 0) return -1;
	else if (tmpscore == 1) return 1;

	//terminal case for already done the board (tie)
	if (boardCount == 9) {
		return 0;
	}

	return tmpscore;
}

int matchStatus(int step, int currentBoard[3][3])
{
	switch (BoardCheck(step, currentBoard))
	{
	case 0:
		cout << "Tie(0)";
		return 0;
	case 1:
		cout << "(X) Player Win! (-1)";
		return 1;
	case -1:
		cout << "(O) Computer Win!(+1)";
		return -1;
	}
	return -2;
}

void playerChoice() 
{
	struct boardIndex playerIndex = { -1, -1 };
	cout << "player first (x)" << endl;
	cout << "Please choose place you will check(x, y) using 1-3 than 0-2: ";

	int x, y;

	cin >> x >> y;
	while (x <= 0 || y <= 0 || x > 3 || y > 3 || board[x - 1][y - 1] != -1)
	{
			cout << "Wrong input, please try again: ";
			cin >> x >> y;
	}
	board[x - 1][y - 1] = 1;

	BoardShowing(board);
	step++;
	int test = matchStatus(step, board);
	if (step == 9 || matchStatus(step, board) != -2) return;
	else computerChoice();
}

void computerChoice()
{
	cout << "computer first(o)" << endl;
	cout << "All possible choice of computer: \n";

	replicatedBoard(board, emuBoard);
	//store value from old array first

	Minimax(step, emuBoard, true, INT_MIN, INT_MAX);
	replicatedBoard(bestBoard, board);

	BoardShowing(board);
	step++;
	
	if (matchStatus(step, board) != -2) return;
	else playerChoice();
}

int Minimax(int currentstep, int nextBoard[3][3], bool isComputerTurn, int alpha, int beta)
{
	int answer = BoardCheck(currentstep, nextBoard);
	if (answer >= -1 && answer <= 1)
	{ //terminal state
		return answer;
	}

	//tree case	
	if (isComputerTurn)
	{
		int checkscore = INT_MAX;
		for (auto item : possiblePos)
		{
			int a = (item - 1) / 3;
			int b = (item - 1) - a * 3;

			if (nextBoard[a][b] == -1)
			{
				//cout << "Min first\n";
				nextBoard[a][b] = 0;

				//cout << "[" << item << "]:\n";

				//BoardShowing(nextBoard);

				
				int lastcheckscore = checkscore;
				int test = Minimax(currentstep + 1, nextBoard, !isComputerTurn, alpha, beta);
				checkscore = min(checkscore, test);

				//beta = min(beta, checkscore); if (beta <= alpha) break;

				if (lastcheckscore != checkscore && currentstep == step) //if answer is right
				{
					//cout << "\nWe will choose: \n";

					replicatedBoard(nextBoard, bestBoard);
				//	BoardShowing(bestBoard);
				}


				//cout << "\nMin: " << checkscore << endl;
				//return old base
				nextBoard[a][b] = -1;
			}

		}

		return checkscore;
	}

	//else
	int checkscore = INT_MIN;
	for (auto item : possiblePos)
	{
		int a = (item - 1) / 3;
		int b = (item - 1) - a * 3;
		if (nextBoard[a][b] == -1)
		{
			//cout << "Max first\n";
			nextBoard[a][b] = 1;

			//test	
			//cout << "[" << item << "]:\n";

			//BoardShowing(nextBoard);

			int test = Minimax(currentstep + 1, nextBoard, !isComputerTurn, alpha, beta);

			checkscore = max(checkscore, test);
			//cout << "\nMax: " << checkscore << endl;

			//alpha = max(alpha, checkscore); if (beta <= alpha) break;

			nextBoard[a][b] = -1;
		}
	}

	return checkscore;
}

int CountBoard()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != -1)
			{
				step++;
			}
			else
			{
				possiblePos.push_back((i * 3 + j) + 1);
				//cout << (i * 3 + j) + 1 << endl;

			}
		}
	}
	cout << "Current step: " << step << endl;
	return step;
}



int main()
{
	cout << "Welcome to Tic_Tac_Toe" << endl;

	int step = CountBoard(); //using once for count the board
	BoardShowing(board);

	if (step == 0) 
	{
		playerChoice(); //player always first
	}
	else
	{
		if (step % 2 == 0) playerChoice(); //player
		else computerChoice();//computer
	}
	
}

//default max = player, min = computer
//player = x, computer = o
//Note:
/*
if we dont start anything, the game will judge player first, then computer
if we have any postion (>1 and almost to the end) the game will look at the game and see who will go first
*/