#include "Graphic.h"
#include <string>

Setting::Setting(const InitData& init) : IScene(init) {
	if (!getData().termflag) {
		getData().termflag = System::GetTerminationTriggers();
		System::SetTerminationTriggers(0);
	}
	Window::SetTitle(U"オセロ?");
}

void Setting::update() {
	const Array<String> onoffstr = { U"オフラインで交互にプレイする", U"オンラインでプレイする" };
	const Array<String> netmodestr = { U"ホスト(部屋作成)", U"ゲスト(部屋参加)", U"オートマッチ" };
	FontAsset(U"Menu")(U"ゲームモード").draw(Vec2(128, 128), ColorF(0.0, 0.5));
	SimpleGUI::RadioButtons(getData().playmode, onoffstr, Vec2(512, 128));
	if (getData().playmode == 1) {
		FontAsset(U"Menu")(U"IPアドレス/ドメイン").draw(Vec2(128, 256), ColorF(0.0, 0.5));
		SimpleGUI::TextBox(ip, Vec2(512, 256));
		FontAsset(U"Menu")(U"オンラインモード").draw(Vec2(128, 320), ColorF(0.0, 0.5));
		SimpleGUI::RadioButtons(onlinemode, netmodestr, Vec2(512, 320));
		if (onlinemode == 1) {
			FontAsset(U"Menu")(U"部屋番号").draw(Vec2(128, 448), ColorF(0.0, 0.5));
			SimpleGUI::TextBox(room, Vec2(512, 448));
		}
		if (onlinemode == 0) {
			SimpleGUI::CheckBox(sizecheck, U"サイズ指定(0~8)", Vec2(128, 448));
			if (sizecheck) {
				FontAsset(U"Menu")(U"縦:").draw(Vec2(512, 448), ColorF(0.0, 0.5));
				SimpleGUI::TextBox(texty, Vec2(544, 448),64);
				FontAsset(U"Menu")(U"横:").draw(Vec2(640, 448), ColorF(0.0, 0.5));
				SimpleGUI::TextBox(textx, Vec2(672, 448),64);
			}
			if (onlinemode == 0 || onlinemode == 1) {
				SimpleGUI::CheckBox(passcheck, U"パスワード", Vec2(128, 512));
				if (passcheck)SimpleGUI::TextBox(pass, Vec2(512, 512));
			}
		}
	}
	else {
		SimpleGUI::CheckBox(sizecheck, U"サイズ指定(0~8)", Vec2(128, 320));
		if (sizecheck) {
			FontAsset(U"Menu")(U"縦:").draw(Vec2(512, 320), ColorF(0.0, 0.5));
			SimpleGUI::TextBox(texty, Vec2(544, 320), 64);
			FontAsset(U"Menu")(U"横:").draw(Vec2(640, 320), ColorF(0.0, 0.5));
			SimpleGUI::TextBox(textx, Vec2(672, 320), 64);
		}
	}

	if (SimpleGUI::ButtonAt(U"開始", Scene::Center().moveBy(0,300),500)) {
		if (getData().playmode == 0) {
			if (sizecheck == 0) {
				getData().game.reset(new Game());
			}
			else {
				int x = ParseOr<int>(textx.text, -1), y = ParseOr<int>(texty.text, -1);
				if (x < 0 || y < 0 || x>8 || y>8) {
					System::ShowMessageBox(U"エラー", U"サイズ指定が不正です", MessageBoxStyle::Error);
					return;
				}
				getData().game.reset(new Game(x, y));
				if (KeyD.pressed())getData().debug = true;
			}
		}
		else {
			getData().net.reset(new Net());
			if (getData().net->makeconnect(ip.text.narrow())) {
				System::ShowMessageBox(U"エラー", U"サーバーに接続できませんでした", MessageBoxStyle::Error);
				return;
			}
			if (onlinemode == 0) {
				if (sizecheck == 0) {
					getData().game.reset(new Game());
				}
				else {
					int x = ParseOr<int>(textx.text, -1), y = ParseOr<int>(texty.text, -1);
					if (x < 0 || y < 0 || x>8 || y>8) {
						System::ShowMessageBox(U"エラー", U"サイズ指定が不正です", MessageBoxStyle::Error);
						return;
					}
					getData().game.reset(new Game(x, y));
				}
				if (passcheck == 0) {
					getData().room = getData().net->makeroom(getData().game->board->boardx / 2, getData().game->board->boardy / 2);
				}
				else {
					getData().room = getData().net->makeroom(getData().game->board->boardx / 2, getData().game->board->boardy / 2, pass.text.narrow());
				}
				if (getData().room == -1) {
					System::ShowMessageBox(U"エラー", U"部屋の作成に失敗しました", MessageBoxStyle::Error);
					return;
				}
				getData().onlinemode = -1;
			}
			else if (onlinemode == 1) {
				std::tuple<int, int> size;
				try {
					getData().room = ParseInt<long long>(room.text, Arg::radix = 16);
				}
				catch (ParseError & e) {
					System::ShowMessageBox(U"エラー", U"部屋番号が不正です", MessageBoxStyle::Error);
				}
				if (passcheck == 0) {
					size = getData().net->login(getData().room);
				}
				else {
					size = getData().net->login(getData().room, pass.text.narrow());
				}
				if (std::get<0>(size) == -1) {
					System::ShowMessageBox(U"エラー", U"部屋への参加に失敗しました", MessageBoxStyle::Error);
					return;
				}
				getData().game.reset(new Game(std::get<0>(size), std::get<1>(size)));
				getData().onlinemode = 1;
			}
			else {
				getData().room = getData().net->automatch();
				if (getData().room == 0) {
					getData().game.reset(new Game());
					getData().room = getData().net->makeroom(getData().game->board->boardx / 2, getData().game->board->boardy / 2);
					if (getData().room == -1) {
						System::ShowMessageBox(U"エラー", U"部屋の作成に失敗しました", MessageBoxStyle::Error);
						return;
					}
					getData().onlinemode = -1;
				}
				else if (getData().room != -1) {
					std::tuple<int, int> size;
					size = getData().net->login(getData().room);
					if (std::get<0>(size) == -1) {
						System::ShowMessageBox(U"エラー", U"部屋への参加に失敗しました", MessageBoxStyle::Error);
						return;
					}
					getData().game.reset(new Game(std::get<0>(size), std::get<1>(size)));
					getData().onlinemode = 1;
				}
				else {
					System::ShowMessageBox(U"エラー", U"オートマッチ中に不正な応答がありました", MessageBoxStyle::Error);
					return;
				}
			}
		}
		changeScene(State::Graph);
	}

	if ((System::GetUserActions() & getData().termflag) != 0) {
		System::Exit();
	}
}

void Setting::draw() const {

}

Graph::Graph(const InitData& init) : IScene(init) {
	black = Texture(U"black.bmp");
	white = Texture(U"white.bmp");
	bg = Texture(U"green.bmp");
	changeturn(getData().game->turn);
	if (getData().playmode == 1) {
		netwait();
		netthread = std::thread([this] {
			while (getData().net->closed == 0) {
				std::tuple<std::string, int, int> action = getData().net->get();
				if (std::get<0>(action).find("nodata") != std::string::npos) {
					getData().net->closed = 1;
				}
				else if (std::get<0>(action).find("FREEPUT") != std::string::npos && getData().onlinemode != getData().game->turn) {
					getData().game->freeput(std::get<1>(action), std::get<2>(action));
					netchangeturn(getData().onlinemode == getData().game->turn, getData().game->turn);
					draw();
				}
				else if (std::get<0>(action).find("PUT") != std::string::npos && getData().onlinemode != getData().game->turn) {
					getData().game->put(std::get<1>(action), std::get<2>(action));
					netchangeturn(getData().onlinemode == getData().game->turn, getData().game->turn);
					draw();
				}
				else if (std::get<0>(action).find("CLOSED") != std::string::npos) {
					getData().net->closed = 1;
				}
				else if (std::get<0>(action).find("READY") != std::string::npos) {
					netchangeturn(getData().onlinemode == getData().game->turn, getData().game->turn);
					getData().net->started = 1;
					getData().net->ready = 1;
				}
			}
			});
	}
}

void Graph::update() {
	if (KeyF.up()) {
		freeput = !freeput;
	}
	if (MouseL.up()) {
		int x = Cursor::Pos().x / (Scene::Size().x / 16);
		int y = Cursor::Pos().y / (Scene::Size().y / 16);
		if (getData().playmode == 0 || (getData().onlinemode == getData().game->turn && getData().net->ready)) {
			if (freeput == false) {
				if (getData().game->put(x, y)) {
					if (getData().playmode == 1)getData().net->put(x, y);
				}
			}
			else if (getData().game->freeput(x, y)) {
				if (getData().playmode == 1)getData().net->freeput(x, y);
			}
			if (getData().playmode == 0)changeturn(getData().game->turn);
			else netchangeturn(getData().onlinemode == getData().game->turn, getData().onlinemode);
		}
	}

	if (getData().playmode == 1 && getData().net->closed == 1 && getData().net->ready == 1) {
		System::ShowMessageBox(U"通知", U"接続が切断されました", MessageBoxStyle::Warning);
		Window::SetTitle(U"オセロ?:ゲーム終了(Eキーで設定に戻る)");
		getData().net->ready = 0;
	}

	if (KeyE.up()) {
		if (System::ShowMessageBox(U"確認", U"本当にこのゲームを終了して戻りますか?", MessageBoxStyle::Question, MessageBoxButtons::YesNo) == MessageBoxSelection::Yes) {
			if (getData().playmode == 1) {
				getData().net->closing();
				netthread.join();
				getData().net.release();
			}
			changeScene(State::Setting);
		}
	}

	if ((System::GetUserActions() & getData().termflag) != 0) {
		if (System::ShowMessageBox(U"確認", U"本当にこのゲームを終了しますか?", MessageBoxStyle::Question, MessageBoxButtons::YesNo) == MessageBoxSelection::Yes) {
			if (getData().playmode == 1) {
				getData().net->closing();
				netthread.join();
				getData().net.release();
			}
			System::Exit();
		}
	}
}

void Graph::changeturn(int turn) {
	if (turn == 1)	Window::SetTitle(U"オセロ?:白番です(Eキーで設定に戻る)");
	if (turn == -1)	Window::SetTitle(U"オセロ?:黒番です(Eキーで設定に戻る)");
}

void Graph::netchangeturn(int you, int turn) {
	std::u32string title = U"オセロ?:";
	if (you == 1) {
		title += U"あなたの番(";
		if (turn == -1)title += U"黒";
		else title += U"白";
		title += U")です(Eキーで設定に戻る)";
	}
	else title += U"相手の番です(Eキーで設定に戻る)";
	Window::SetTitle(title.c_str());
}


void Graph::netwait() {
	Window::SetTitle(U"オセロ?:対戦相手待ち(Eキーで設定に戻る)");
}

void Graph::draw() const {
	bg.draw();
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (getData().game->board->board[i][j] == -1)black.draw(Vec2(i * 66, j * 66));
			else if (getData().game->board->board[i][j] == 1)white.draw(Vec2(i * 66, j * 66));
		}
	}
	if (getData().game->full) {
		String text = U"黒:" + Format(getData().game->b) + U"\n白:" + Format(getData().game->w) + U"\n総ターン数:" + Format(getData().game->howturn);
		System::ShowMessageBox(U"ゲーム終了", text, MessageBoxStyle::Info);
		Window::SetTitle(U"オセロ?:ゲーム終了(Eキーで設定に戻る)");
		getData().game->full = false;
	}
}
