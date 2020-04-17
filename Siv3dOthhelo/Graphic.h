#pragma once
#include <Siv3D.hpp>
#include <vector>
#include "Game.h"
#include "net.h"
enum class State
{
	Kagawa,
	Setting,
	Graph
};
struct SysState {
	uint32 termflag;
	size_t playmode;
	int onlinemode;
	std::unique_ptr<Game> game;
	std::unique_ptr<Net> net;
	long long room;
	bool debug = false;
	char kagawa = 0;
	Timer kagawatimer;
};
using MyApp = SceneManager<State, SysState>;

class KagawaCheck : public MyApp::Scene {
public:
	KagawaCheck(const InitData& init);
	void update() override;
	void draw() const override;
};

class Setting : public MyApp::Scene {
private:
	bool passcheck = false, sizecheck = false;
	TextEditState ip, room, pass, textx, texty;
	size_t  onlinemode;
public:
	Setting(const InitData& init);
	void update() override;
	void draw() const override;
};

#include <thread>
class Graph : public MyApp::Scene {
private:
	bool freeput = false;
	Texture black, white, bg;
	std::thread netthread;
public:
	Graph(const InitData& init);
	void update() override;
	void changeturn(int turn);
	void netchangeturn(int you, int turn);
	void netwait();
	void draw() const override;
};
