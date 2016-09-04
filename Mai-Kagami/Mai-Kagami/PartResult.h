#ifndef __PARTRESULT_H_INCLUDED__
#define __PARTRESULT_H_INCLUDED__

#include "DxLib.h"
#include "DrawText.h"
#include "DrawObject.h"
#include "Button.h"
#include "Songs.h"
#include "Scene.h"
#include "PartResultDefine.h"
#include "SeetingPop.h"
#include "Touch.h"

class PartResult : public SubScene {
public:
	PartResult(Font *font, Songs *songs, Touch *touch);
	void Load();
	int Switch(const int scene);
	~PartResult();
private:
	void ContentUpdate();
	void ContentView();
	MyDrawTextLine *title; //採点結果画面タイトル
	MyDrawText *part[100], *speed[100], *score[100];
	MyDrawCircle *circle[100];
	Button *button; //次へボタン
	Song *song;
	Songs *songs;
	Font *font;
	int partMax;
};

class PartFinish : public SubScene {
public:
	PartFinish(Font *font, Touch *touch);
	int Switch(const int scene);
	~PartFinish();
private:
	void ContentUpdate();
	void ContentView();
	BlackBox *blackBox;
	Button *button[4];
};

#endif