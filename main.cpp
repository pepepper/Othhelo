#define SDL_MAIN_HANDLED
#include <memory>
#include "Graphic.h"
#include "Game.h"
#include "dialogbox.h"
#include <string>
#include <iostream>
#include <typeinfo>

int main(int argc, char *argv[]) {
	std::string ip, port, user, pass, arg;
	SDL_Event e;
	int x, y, mode = -1, netmode, first;
	std::unique_ptr<Game> game;

	std::cout << "モードを選択してください" << std::endl << "0:オフラインで交互にプレイする 1:オンラインでプレイする場合 :";
	do {
		std::cin >> arg;
		if (!arg.compare("0")) {
			mode = 0;
			break;
		}
		if (!arg.compare("1")) {
			std::cout << "まだ未実装やどぇw" << std::endl;
		}
		std::cout << "正しい数値を入力してくだせえ" << std::endl;
	} while (1);
	std::cout << "盤面サイズを指定しますか?" << std::endl << "0:指定しない 1:指定する :";
	do {
		std::cin >> arg;
		if (!arg.compare("0")) {
			game.reset(new Game());
			break;
		}
		if (!arg.compare("1")) {
			std::string sx, sy;
			try {
				std::cout << "縦のサイズを入力してください:";
				std::cin >> sy;
			} catch (const std::invalid_argument& e) {
				std::cout << "数値ではありません:終了します";
				return 1;
			}
			try {
				std::cout << "横のサイズを入力してください:";
				std::cin >> sx;
			} catch (const std::invalid_argument& e) {
				std::cout << "数値ではありません:終了します";
				return 1;
			}

			game.reset(new Game(std::stoi(sx), std::stoi(sy)));
			break;
		}
		std::cout << "正しい数値を入力してくだせえ" << std::endl;
	} while (1);
	/*
		for (int i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-ip"))
				ip = argv[i += 1];
			if (!strcmp(argv[i], "-port"))
				port = argv[i += 1];
			if (!strcmp(argv[i], "-user"))
				user = argv[i += 1];
			if (!strcmp(argv[i], "-h"))
				netmode = 0;
			if (!strcmp(argv[i], "-p"))
				first = 1;
			if (!strcmp(argv[i], "-g"))
				netmode = 1;
			if (!strcmp(argv[i], "-pass"))
				pass = argv[i += 1];
		}
		*/

	SDL_Init(SDL_INIT_EVERYTHING);
	Graphic graphic;
	dialogbox dialog;

	graphic.StartGame();
	graphic.Put(game->board->delta);
	graphic.changeturn(game->turn);
	graphic.update();
	while (true) {
		while (SDL_WaitEvent(&e)) {
			switch (e.type) {
				case SDL_WINDOWEVENT:
					if (e.window.event == SDL_WINDOWEVENT_EXPOSED) {
						graphic.update();
					}
					break;
				case SDL_MOUSEBUTTONUP:
					x = (int)(e.button.x / 48) - 4;
					y = (int)(e.button.y / 48) - 4;
					if (game->put(x, y)) {
						graphic.Put(game->board->delta);
						graphic.changeturn(game->turn);
						graphic.update();
					}
					if (game->full) {
						dialog.EndGameDialogBox(game->b, game->w, game->howturn);
						game->full = false;
					}
					if (game->full)dialog.EndGameDialogBox(game->b, game->w, game->howturn);
					break;
				case SDL_QUIT:
					if (dialog.QuitinGameDialogbox()) {
						std::cout<<SDL_GetError();
						game.release();
						graphic.~Graphic();
						SDL_Quit();
						return 0;
					}
					break;
			}
		}
	}
	return 0;
}