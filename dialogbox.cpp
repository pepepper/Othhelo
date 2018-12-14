#include "dialogbox.h"
#include <string>

dialogbox::dialogbox() {}

int dialogbox::QuitinGameDialogbox() {
	boxer::Selection selection;
	selection=boxer::show(u8"本当にこのゲームを終了しますか?", u8"確認", boxer::Style::Question, boxer::Buttons::YesNo);
	if(selection == boxer::Selection::Yes){
		return 1;
	}else{
		return 0;
	}
}

int dialogbox::EndGameDialogBox(int black, int white, int turn) {
	std::string str = u8"黒:" + std::to_string(black) + u8"\n白:" + std::to_string(white) + u8"\n総ターン数:" + std::to_string(turn);
	boxer::Selection selection;
	boxer::show(str.c_str(), u8"ゲーム終了", boxer::Style::Warning,boxer::Buttons::OK);
	return 1;
}

dialogbox::~dialogbox() {}

