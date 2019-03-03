#include "Boards.h"

Boards::Boards(int x, int y): delta(40, std::vector<int>(3, 0)){
	board.resize(x);
	for(int i = 0; i < x; i++)board[i].resize(y);
	boardx = x;
	boardy = y;
	xoffset = x / 2 - 4;
	yoffset = y / 2 - 4;
	noCheckPut(boardx / 2 - 1, boardy / 2 - 1, 1);
	noCheckPut(boardx / 2, boardy / 2, 1);
	noCheckPut(boardx / 2, boardy / 2 - 1, -1);
	noCheckPut(boardx / 2 - 1, boardy / 2, -1);
}

void Boards::Reverse(int x, int y, int vect_x, int vect_y, int turn){
	int i = 0;
	board[x][y] = turn;
	while(delta[i][0]){ i++; }
	delta[i][0] = turn;
	delta[i][1] = x - xoffset;
	delta[i][2] = y - yoffset;
	x += vect_x;
	y += vect_y;
	while(x >= 0 && x < boardx && y >= 0 && y < boardy){
		if(board[x][y] == turn) break;
		board[x][y] = turn;
		while(delta[i][0]){ i++; }
		delta[i][0] = turn;
		delta[i][1] = x - xoffset;
		delta[i][2] = y - yoffset;
		x += vect_x;
		y += vect_y;
	}
}

bool Boards::isPutable(int x, int y, int deltax, int deltay, int turn){
	x += deltax;
	y += deltay;
	if(x < 0 || x >= boardx || y < 0 || y >= boardy)return false;
	if(board[x][y] == turn)return false;
	if(board[x][y] == 0)return false;

	x += deltax;
	y += deltay;
	while(x >= 0 && x < boardx  &&  y >= 0 && y < boardy){
		if(board[x][y] == 0)return false;
		if(board[x][y] == turn)return true;
		x += deltax;
		y += deltay;
	}
	return false;
}

bool Boards::isPutable(int x, int y, int turn){
	bool ret = false;
	x += xoffset;
	y += yoffset;
	if(x < 0 || x >= boardx || y < 0 || y >= boardy || board[x][y] != 0) return ret;//1 white -1 black

	if(isPutable(x, y, 1, 0, turn)){
		ret = true;
	}    //右
	if(isPutable(x, y, 0, 1, turn)){
		ret = true;
	}    //下
	if(isPutable(x, y, -1, 0, turn)){
		ret = true;
	}    //左
	if(isPutable(x, y, 0, -1, turn)){
		ret = true;
	}    //上
	if(isPutable(x, y, 1, 1, turn)){
		ret = true;
	}    //右下
	if(isPutable(x, y, -1, -1, turn)){
		ret = true;
	}    //左上
	if(isPutable(x, y, 1, -1, turn)){
		ret = true;
	}    //右上
	if(isPutable(x, y, -1, 1, turn)){
		ret = true;
	}    //左下

	return ret;
}

bool Boards::Put(int x, int y, int turn){
	bool ret = false;
	x += xoffset;
	y += yoffset;
	if(x < 0 || x >= boardx || y < 0 || y >= boardy || board[x][y] != 0) return ret;//1 white -1 black

	if(isPutable(x, y, 1, 0, turn)){
		Reverse(x, y, 1, 0, turn);
		ret = true;
	}    //右
	if(isPutable(x, y, 0, 1, turn)){
		Reverse(x, y, 0, 1, turn);
		ret = true;
	}    //下
	if(isPutable(x, y, -1, 0, turn)){
		Reverse(x, y, -1, 0, turn);
		ret = true;
	}    //左
	if(isPutable(x, y, 0, -1, turn)){
		Reverse(x, y, 0, -1, turn);
		ret = true;
	}    //上
	if(isPutable(x, y, 1, 1, turn)){
		Reverse(x, y, 1, 1, turn);
		ret = true;
	}    //右下
	if(isPutable(x, y, -1, -1, turn)){
		Reverse(x, y, -1, -1, turn);
		ret = true;
	}    //左上
	if(isPutable(x, y, 1, -1, turn)){
		Reverse(x, y, 1, -1, turn);
		ret = true;
	}    //右上
	if(isPutable(x, y, -1, 1, turn)){
		Reverse(x, y, -1, 1, turn);
		ret = true;
	}    //左下

	return ret;
}

void Boards::noCheckPut(int x, int y, int turn){
	int i = 0;
	board[x][y] = turn;
	while(delta[i][0]){ i++; }
	delta[i][0] = turn;
	delta[i][1] = x - xoffset;
	delta[i][2] = y - yoffset;
}

bool Boards::isFull(int turn){
	for(int x = 0; x < boardx; x++){
		for(int y = 0; y < boardy; y++){
			if(board[x][y] == 0)
				if(isPutable(x, y, turn))return false;
		}
	}
	return true;
}

bool Boards::isSkipable(int turn){
	return false;
}

std::pair<int, int> Boards::Count(){
	int b = 0, w = 0;
	for(int i = 0; i < boardx; i++){
		for(int j = 0; j < boardy; j++){
			if(board[i][j] == 1)w++;
			else if(board[i][j] == -1)b++;
		}
	}
	return std::pair<int, int>(w, b);
}

Boards::~Boards(){
	std::vector<std::vector<int>>().swap(board);
}
