#pragma once
#include <vector>
#include <utility>
class Boards{
	public:
	Boards(int x, int y);
	~Boards();
	bool isPutable(int x, int y, int deltax, int deltay, int turn);
	bool isPutable(int x, int y, int turn);
	bool Put(int x, int y, int turn);
	bool isFull(int turn);
	bool isSkipable(int turn);
	std::vector<std::vector<int>> delta;
	std::pair<int, int> Count();
	std::vector<std::vector<int>> board;
	int boardx, boardy, xoffset, yoffset;
	private:
	void noCheckPut(int x, int y, int turn);
	void Reverse(int x, int y, int vect_x, int vect_y, int turn);//石をひっくり返す

};

