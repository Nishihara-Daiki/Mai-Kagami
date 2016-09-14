#ifndef __PLAYSCREENOBJECT_H_INCLUDED__
#define __PLAYSCREENOBJECT_H_INCLUDED__

#include "DxLib.h"
#include "DrawObject.h"
#include "SeetingPop.h"
#include "DrawText.h"

//進捗バー
class PlayBar {
public:
	PlayBar(Font *font, const double* sceneOpacity);
	void Load(Song *song);
	void Update();
	void View();
	~PlayBar();
private:
	Font *font;
	Song *song;
	MyDrawBar *barAll, *barNow;
	MyDrawCircle *circle[2];
	MyDrawTextV *part[10];
	const double *sceneOpacity;
};

//カウントダウン画面用再生三角形
class PlayTriangle : public MyDrawTriangle {
public:
	PlayTriangle(const float x, const float y, const double* sceneOpacity);
};


//カウントダウン画面
class CountDown : public SubScene {
public:
	CountDown(Font *font, const int thisScene, const int playScene);
	int Switch(const int scene);
	~CountDown();
private:
	void ContentUpdate();
	void ContentView();
	int count; //カウンタ
	int thisScene, playScene; //CountDown画面のシーン、プレイモードのシーン
	BlackBox *blackBox;
	MyDrawText *text;
	MyDrawCircle *circle;
	MyDrawCircleGauge *countCircle1;
	MyDrawCircle *countCircle2;
	PlayTriangle *playTriangle;
	const int max = 120;
};

#endif