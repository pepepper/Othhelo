#include "dialogbox.h"
#include <string>

dialogbox::dialogbox() {}

int dialogbox::QuitinGameDialogbox() {
	int ret;
	SDL_ShowMessageBox(&QuitinGameDialogDatas, &ret);
	return ret;
}

int dialogbox::QuitDialogbox() {
	int ret;
	SDL_ShowMessageBox(&QuitDialogDatas, &ret);
	return ret;
}

int dialogbox::NoargsDialogbox() {
	int ret;
	SDL_ShowMessageBox(&NoargsDialogDatas, &ret);
	return ret;
}

int dialogbox::EndGameDialogBox(int black, int white, int turn) {
	std::string str = u8"黒:" + std::to_string(black) + u8"\n白:" + std::to_string(white) + u8"\n総ターン数:" + std::to_string(turn);
	SDL_MessageBoxData EndGameDialogDatas = {
		SDL_MESSAGEBOX_WARNING, /* .flags */
		NULL, /* .window */
		u8"ゲーム終了", /* .title */
		str.c_str(), /* .message */
		1, /* .numbuttons */
		&EndDialogButtons, /* .buttons */
		NULL /* .colorScheme */
	};
	int ret;
	SDL_ShowMessageBox(&EndGameDialogDatas, &ret);
	return ret;
}

dialogbox::~dialogbox() {}

