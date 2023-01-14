// 限制fps在60，或者用计时器控制游戏不会因帧率变化导致速度变化
// 想法：更改公式计算每一帧每几帧对应的帧率，提高帧率计算的精确度，同时
// 将帧率计数器和限制器合并提高运行效率
#pragma once
#include <SDL.h>
#include <SDL_FontCache.h>
#include <sstream>
#include <iomanip>
#include <format>
#include "timer.hpp"
#include "texture.hpp"

extern const unsigned int WINDOW_HEIGHT;
extern SDL_Renderer* gRenderer;

class FpsTimer{
public:
	FpsTimer();
	~FpsTimer();
	void start();
	void update();
	void render();
private:
	double CalcFps();
private:
	Timer t;
	FC_Font* font;
	int cntFrame;
	std::stringstream text;
};
class FpsCapper{
public:
	int getTargetFps() const;
	void setTargetFps(const int&);
	void start();
	void cap();
private:
	int targetFps;
	int targetTicks;
	Timer t;
};

FpsTimer::FpsTimer() {
	font = FC_CreateFont();
	FC_LoadFont(font, gRenderer, "assets/font/jetbrains_mono.ttf", 20, SDL_Color{0, 0, 0, 255}, TTF_STYLE_BOLD);
	if (font == nullptr) throw;
	cntFrame = 0;
}
FpsTimer::~FpsTimer() {
	FC_FreeFont(font);
	// TODO: there's a bug causing memory fault
}
void FpsTimer::start() {
	t.start();
}
void FpsTimer::update() {
	cntFrame++;
	if (cntFrame == 1000000) { // to prevent overflow and adjust result
		t.start();
		cntFrame = 0;
	}
}
void FpsTimer::render() {
	text.str("");
	double avgFps = CalcFps();
	if (avgFps > 70) {
		avgFps = 60;
	}
	text << std::setprecision(3) << avgFps;
	FC_Draw(font, gRenderer, 0, WINDOW_HEIGHT - 30, text.str().c_str());
}
double FpsTimer::CalcFps() {
	return (cntFrame * 1.0) / ((t.getTicks() * 1.0) / 1000.0);
}

int FpsCapper::getTargetFps() const {
	return targetFps;
}
void FpsCapper::setTargetFps(const int& x) {
	targetFps = x;
	targetTicks = 1000 / targetFps;
}
void FpsCapper::start() {
	t.start();
}
void FpsCapper::cap() {
	int frameTicks = t.getTicks();
	if (frameTicks < targetTicks) {
		SDL_Delay(targetTicks - frameTicks);
	}
}
