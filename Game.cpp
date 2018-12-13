#include "Game.h"
#include <random>
#include <utility>

Game::Game() {
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution<int> dist(4, 8);
	boardx = dist(engine) * 2;
	boardy = dist(engine) * 2;
	board = new Boards(boardx, boardy);
	turn = -1;
	howturn = 0;
}

Game::Game(int x,int y) {
	board = new Boards(boardx=x*2, boardy=y*2);
	turn = -1;
	howturn = 0;
}


Game::~Game() {
	delete board;
}

bool Game::put(int x, int y) {
	int temp1 = x, temp2 = y;
	if (board->Put(temp1, temp2, turn)) {
		turn *= -1;
		howturn++;
		full = board->isFull();
		std::pair<int, int> koma(board->Count());
		w = koma.first;
		b = koma.second;
		if (w == 0 || b == 0)full = true;
		canPass();
		return true;
	}
	return false;
}

void Game::canPass() {
	for (int x = 0; x < boardx; x++) {
		for(int y=0;y<boardy;y++){
			if (board->isPutable(x, y, turn))return;
		}
	}
	turn *= -1;
}