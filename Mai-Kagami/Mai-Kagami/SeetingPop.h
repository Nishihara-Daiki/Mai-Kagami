#ifndef __SETTINGPOP_H_INCLUDED__
#define __SETTINGPOP_H_INCLUDED__

#include "DxLib.h"
#include "DrawObject.h"
#include "DrawText.h"
#include "Button.h"
#include "Font.h"
#include "Songs.h"
#include "Touch.h"
#include "Scene.h"

//ポップアップ用四角形（黒色半透明全画面）
class BlackBox : public MyDrawBox {
public:
	BlackBox();
private:
};

//スピードオプション表示
class SpeedOption {
public:
	SpeedOption(Font *font, Songs *songs, Touch *touch);
	void Check();
	void View();
	~SpeedOption();
private:
	Button *button[2];
	MyDrawText *speed[2];
	Songs *songs;
};

//区間設定オプション表示
class PartOption {
public:
	PartOption(Font *font, Songs *songs, Touch *touch);
	void Init();
	void Check();
	void View();
	~PartOption();
private:
	Button *button[4];
	MyDrawText *part[4];
	Songs *songs;
	Song *song;
};

//スピードオプションポップアップ
class SpeedPop : public SubScene {
public:
	SpeedPop(Font *font, Songs *songs, Touch *touch);
	void Load();
	~SpeedPop();
protected:
	void ContentUpdate();
	void ContentView();
	Songs *songs;
	Song *song;
	SpeedOption *speedOption;
	BlackBox *blackBox;
	Button *button;
	MyDrawText *text;
};

//区間設定オプションポップアップ
class PartPop : public SubScene {
public:
	PartPop(Font *font, Songs *songs, Touch *touch);
	void Load();
	~PartPop();
protected:
	void ContentUpdate();
	void ContentView();
	void Init();
	Songs *songs;
	Song *song;
	PartOption *partOption;
	BlackBox *blackBox;
	Button *button;
	MyDrawText *text;
};


#endif