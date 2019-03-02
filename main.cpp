#define SDL_MAIN_HANDLED
#include <memory>
#include "Graphic.h"
#include "Game.h"
#include "dialogbox.h"
#include <string>
#include <iostream>
#include <typeinfo>

int main(int argc, char *argv[]) {
	std::string ip, pass, arg;
	SDL_Event e;
	int x, y, mode = -1, netmode = -1;
	std::unique_ptr<Game> game;
	//部屋番号指定
	std::cout << "モードを選択してください" << std::endl << "0:オフラインで交互にプレイする 1:オンラインでプレイする場合 :";
	try {
		std::cin >> arg;
		mode = std::stoi(arg);
		if (mode != 0 && mode != 1)throw std::invalid_argument("");
		if (mode == 1) {
			std::cout << "モードを選択してください" << std::endl << "0:ホストとして部屋を立てる 1:ゲストとして部屋に入る :";
			std::cin >> arg;
			netmode = std::stoi(arg);
			if (netmode != 0 && netmode != 1)throw std::invalid_argument("");
			std::cout << "サーバーのIPアドレスまたはドメインを入力してください:" << std::endl;
			std::cin >> ip;
			if (netmode == 0) std::cout << "パスワードを設定しますか?" << std::endl << "0:設定しない 1:設定する :";
			if (netmode == 0) std::cout << "パスワードが設定されていますか?" << std::endl << "0:設定されている 1:設定されていない :";
			std::cin >> arg;
			if (!arg.compare("1")) {
				std::cout << "パスワードを入力してください:" << std::endl;
				std::cin >> pass;
			}
		}
		if (mode == 0 || netmode == 0) {
			std::cout << "盤面サイズを指定しますか?" << std::endl << "0:指定しない 1:指定する :";
			std::cin >> arg;
			if (!arg.compare("0")) {
				game.reset(new Game());
			}
			else	if (!arg.compare("1")) {
				std::string sx, sy;
				int x, y;

				std::cout << "縦のサイズを入力してください:";
				std::cin >> sy;
				x = std::stoi(sx);

				std::cout << "横のサイズを入力してください:";
				std::cin >> sx;
				y = std::stoi(sy);

				game.reset(new Game(x, y));
			}
			else { throw std::invalid_argument(""); }
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << "入力が不正です:終了します";
		return 1;
	}

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
				break;
			case SDL_QUIT:
				if (dialog.QuitinGameDialogbox()) {
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