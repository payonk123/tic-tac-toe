#include "Game.h"
#include <iostream>


using namespace std;

Game::Game() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			n_matrix[i][j] = -1;

}



int Game::result() {

	//Returning:
	// 1 krzyzyk won
	// 0 kolko won
	// -1 draw
	// -2 game on

	bool ItsNotDraw = true;
	// c helps with estimating if there's a draw

	//CHECKING FOR KRZYZYK - IF WON RETURN 1
	//check columns
	for (int i = 0; i < 3; i++) {
		if (getElement(i, 0) == 1 && getElement(i, 1) == 1
			&& getElement(i, 2) == 1)
			return 1;
		//check rows
		if (getElement(0, i) == 1 && getElement(1, i) == 1
			&& getElement(2, i) == 1)
			return 1;
	}
	//check diagonal from up left to down right
	if (getElement(0, 0) == 1 && getElement(1, 1) == 1
		&& getElement(2, 2) == 1)
		return 1;
	//check diagonal from up right to down left
	if (getElement(0, 2) == 1 && getElement(1, 1) == 1
		&& getElement(2, 0) == 1)
		return 1;

	// CHECKING FOR KOLKO - IF WON RETURN 0 
   //check columns
	for (int i = 0; i < 3; i++) {
		if (getElement(i, 0) == 0 && getElement(i, 1) == 0
			&& getElement(i, 2) == 0)
			return 0;
		//check rows
		if (getElement(0, i) == 0 && getElement(1, i) == 0
			&& getElement(2, i) == 0)
			return 0;
	}
	//check diagonal from up left to down right
	if (getElement(0, 0) == 0 && getElement(1, 1) == 0
		&& getElement(2, 2) == 0)
		return 0;
	//check diagonal from up right to down left
	if (getElement(0, 2) == 0 && getElement(1, 1) == 0
		&& getElement(2, 0) == 0)
		return 0;
	//check if there is a draw (if -1 in any cell - no draw)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (getElement(i, j) == -1)
				ItsNotDraw = false;
		}
	if (ItsNotDraw)
		return -1;
	//no one won nor there's a draw - RETURN -2
	return -2;
};

void Game::setElement(int e, int i, int j) {
	if (n_matrix[i][j] != -1)
		throw 9;
	if (e != 1 && e != 0)
		throw 99;
	if (i < 0 && i > 2 && j < 0 && j > 2)
		throw 999;
	n_matrix[i][j] = e;
};
int Game::getElement(int i, int j) {
	if (i < 0 && i > 2 && j < 0 && j > 2)
		throw 999;
	return n_matrix[i][j];
};


void Game::reset() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			n_matrix[i][j] = -1;
};
