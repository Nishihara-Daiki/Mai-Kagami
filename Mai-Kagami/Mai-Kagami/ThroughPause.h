#ifndef __THROUGHPAUSE_H_INCLUDED__
#define __THROUGHPAUSE_H_INCLUDED__

#include "DxLib.h"
#include "Button.h"
#include "Font.h"
#include "Songs.h"
#include "ThroughDefine.h"
#include "SeetingPop.h"
#include "Touch.h"
#include "Scene.h"

//ポーズボタン画面
class ThroughPauseButton : public SubScene {
public:
	ThroughPauseButton(Touch *touch);
	void Load();
	ThroughScene Switch(const ThroughScene scene);
	void ContentUpdate();
	void ContentView();
	void Delete();
	~ThroughPauseButton();
private:
	CircleGraphButton *pauseButton; //一時停止用ボタン
};

//ポーズ画面
class ThroughPauseScreen : public SubScene {
public:
	ThroughPauseScreen(Font *font, Songs *songs, Touch *touch);
	void Load();
	ThroughScene Switch(const ThroughScene scene);
	void ContentUpdate();
	void ContentView();
	void Delete();
	~ThroughPauseScreen();
private:
	Songs *songs;
	BlackBox *blackBox; //背景半透明黒の四角形
	MyDrawText *title;
	CircleGraphTextButton *button[4];
};

//速度変更画面
class ThroughPauseSetting : public SpeedPop {
public:
	ThroughPauseSetting::ThroughPauseSetting(Font *font, Songs *songs, Touch *touch) : SpeedPop(font, songs, touch) {};
	ThroughScene Switch(const ThroughScene scene);
	void ContentUpdate();
};

//ポーズ関係
class ThroughPause : public SubScene {
public:
	ThroughPause(Font *font, Songs *songs, Touch *touch);
	void Load();
	ThroughScene Switch(const ThroughScene scene);
	void ContentUpdate();
	void ContentView();
	void Delete();
	~ThroughPause();
private:
	Songs *songs;
	boolean flag; //ポーズ中かどうかのフラグ
	ThroughPauseButton *throughPauseButton; //ポーズボタン画面
	ThroughPauseScreen *throughPauseScreen; //ポーズ画面
	ThroughPauseSetting *throughPauseSetting; //速度変更画面
};

#endif