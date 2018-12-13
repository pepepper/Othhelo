#pragma once
#include "SDL2-2.0.8/include/SDL.h"

class dialogbox {
	public:
	dialogbox();
	int NoargsDialogbox();
	int QuitinGameDialogbox();
	int QuitDialogbox();
	int EndGameDialogBox(int black, int white,int turn);
	~dialogbox();

	private:
	const SDL_MessageBoxButtonData QuitDialogButtons[2] = {
		{0, 0, u8"いいえ"	},
		{0, 1, u8"はい"},
	};
		const SDL_MessageBoxButtonData Error[1] = {
		{0, 0, u8"OK..."	},
	};

	const SDL_MessageBoxButtonData EndDialogButtons = 	{0, 0, u8"OK"};

	const SDL_MessageBoxData QuitinGameDialogDatas = {
		SDL_MESSAGEBOX_WARNING, /* .flags */
		NULL, /* .window */
		u8"確認", /* .title */
		u8"失った信頼は戻ってきませんが、本当にこのゲームを終了しますか?", /* .message */
		SDL_arraysize(QuitDialogButtons), /* .numbuttons */
		QuitDialogButtons, /* .buttons */
		NULL /* .colorScheme */
	};

	const SDL_MessageBoxData QuitDialogDatas = {
		SDL_MESSAGEBOX_ERROR, /* .flags */
		NULL, /* .window */
		u8"Oops!", /* .title */
		u8"まだ実装されていません！", /* .message */
		SDL_arraysize(Error), /* .numbuttons */
		Error, /* .buttons */
		NULL /* .colorScheme */
	};

		const SDL_MessageBoxData NoargsDialogDatas = {
		SDL_MESSAGEBOX_ERROR, /* .flags */
		NULL, /* .window */
		u8"Oops!", /* .title */
		u8"コマンド引数がありません！\nメニューから起動してください！", /* .message */
		SDL_arraysize(Error), /* .numbuttons */
		Error, /* .buttons */
		NULL /* .colorScheme */
	};

};

