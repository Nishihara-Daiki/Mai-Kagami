#ifndef __PARTPAUSE_H_INCLUDED__
#define __PARTPAUSE_H_INCLUDED__

#include "DxLib.h"
#include "Button.h"
#include "Font.h"
#include "Songs.h"
#include "PartDefine.h"
#include "SeetingPop.h"
#include "PauseScreen.h"
#include "Touch.h"
#include "Scene.h"
#include "PartOptionPop.h"

//ポーズボタン画面
class PartPauseButton : public SubScene {
public:
	PartPauseButton(Touch *touch, Songs *songs);
	void Load();
	int Switch(const int scene);
	void Delete();
	~PartPauseButton();
private:
	void ContentUpdate();
	void ContentView();
	Songs *songs;
	CircleGraphButton *button[2]; //ボタン
};

//ポーズ画面
class PartPauseScreen : public PauseScreen {
public:
	PartPauseScreen(Font *font, Songs *songs, Touch *touch);
};

class PartOptionPreview3 : public PartOptionPreview {
public:
	PartOptionPreview3(Font *font, Songs *songs, Touch *touch);
	int Switch(const int scene);
	~PartOptionPreview3();
private:
	BlackBox *blackBox;
	void ContentView();
	Button *button;
};

//設定変更画面
class PartPauseSetting : public PartOptionPop {
public:
	PartPauseSetting(Font *font, Songs *songs, Touch *touch);
};

//ポーズ関係
class PartPause : public SubScene {
public:
	PartPause(Font *font, Songs *songs, Touch *touch);
	void Load();
	int Switch(const int scene);
	void Delete();
	~PartPause();
private:
	void ContentUpdate();
	void ContentView();
	Songs *songs;
	boolean flag; //ポーズ中かどうかのフラグ
	PartPauseButton *partPauseButton; //ポーズボタン画面
	PartPauseScreen *partPauseScreen; //ポーズ画面
	PartPauseSetting *partPauseSetting; //設定変更画面
};

#endif