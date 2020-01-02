#include <memory>
#include "Graphic.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include <tuple>
#include <thread>
#include <iomanip>

void Main() {
	Window::Resize(768, 768);
	Scene::Resize(1052, 1052);
	Scene::SetBackground(ColorF(0.2, 0.8, 0.4));
	// 使用するフォントアセットを登録
	FontAsset::Register(U"Menu", 20, Typeface::Bold);

	// シーンと遷移時の色を設定
	MyApp manager;
	manager
		.add<Setting>(State::Setting)
		.add<Graph>(State::Graph);
	while (System::Update()) {
		if (!manager.update()) {
			break;
		}
	}
	return;
}