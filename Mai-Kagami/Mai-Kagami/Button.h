#ifndef __BUTTON_H_INCLUDED__
#define __BUTTON_H_INCLUDED__

#include "DxLib.h"
#include "DrawText.h"
#include "DrawObject.h"
#include "DrawGraph.h"
#include "Touch.h"

#define BUTTON_POS HEIGHT * 0.5
#define BUTTON_INTERVAL HEIGHT * 0.05

//ボタン関係
class Button : public Draw {
public:
	Button(const int num, Touch *touch);
	int GetTouch(); //そのボタンが押されているフレーム数を取得
private:
	virtual void ContentView() = 0; //表示用関数
	Touch *touch; //タッチ
	int num; //ボタン番号
};

//三角形のボタン
class TriangleButton : public Button {
public:
	TriangleButton(Font *font, Touch *touch, const char *str, const int direction, const int num, char *colorName = "Blue");
	void ContentView(double sceneOpacity);
	~TriangleButton();
private:
	MyDrawTriangle2 *myDrawTriangle2;
	MyDrawText *text; //ボタンの文字
};

//説明文付き三角形のボタン
class TriangleButton2 : public Button {
public:
	TriangleButton2(Font *font, Touch *touch, const char *title, const char *str, const int direction, const int num, const float x, const char *colorName);
	void ContentView(double sceneOpacity);
	~TriangleButton2();
private:
	MyDrawText *text; //ボタンの文字
	MyDrawTexts *descriptionText;
	MyDrawTriangle2 *myDrawTriangle2;
	MyDrawBox *myDrawBox;
};

//円のボタン
class CircleButton : public Button {
public:
	CircleButton(Font *font, Touch *touch, const char *str, const int num, char *colorName = "Blue"); //文字右寄せボタン
	CircleButton(Font *font, Touch *touch, const char *str, const int num, const float x, char *colorName = "Blue"); //文字中央寄せボタン
	void ContentView(double sceneOpacity);
	~CircleButton();
private:
	MyDrawText *text; //ボタンの文字
	MyDrawCircle *myDrawCircle;
};

//文字が丸の中にあるボタン
class CircleButton2 : public Button {
public:
	CircleButton2(Font *font, Touch *touch, const char *str, const int num, char *colorName = "Blue");
	void ContentView(double sceneOpacity);
	~CircleButton2();
private:
	MyDrawText *text; //ボタンの文字
	MyDrawCircle *myDrawCircle;
};

//画像付きのボタン
class CircleGraphButton : public Button {
public:
	CircleGraphButton(Touch *touch, const int num, const char *fileName);
	void ContentView(double sceneOpacity);
	void Load();
	void Release();
	~CircleGraphButton();
private:
	MyDrawCircle *myDrawCircle;
	MyDrawGraph *myDrawGraph;
};

//画像、テキスト付きのボタン
class CircleGraphTextButton : public Button {
public:
	CircleGraphTextButton(Font *font, Touch *touch, const char *str, const int num, const char *fileName);
	void Load();
	void ContentView(double sceneOpacity);
	void Release();
	~CircleGraphTextButton();
private:
	MyDrawCircle *myDrawCircle;
	MyDrawGraph *myDrawGraph;
	MyDrawText *text;
};

#endif