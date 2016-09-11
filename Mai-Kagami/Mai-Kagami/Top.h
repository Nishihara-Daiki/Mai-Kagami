#ifndef __TOP_H_INCLUDED__
#define __TOP_H_INCLUDED__

#include "DxLib.h"
#include "DrawText.h"
#include "DrawGraph.h"
#include "DrawObject.h"
#include "Font.h"

//トップロゴ
class TopLogo : public MyDrawGraph {
public:
	TopLogo( const float y);
};

//NFCタッチメッセージ関係
class TopTouchMessage : public MyDrawText {
public:
	TopTouchMessage(Font *font, const float y);
	void Init(); //初期化
	void Update(); //計算
	void View(double sceneOpacity); //表示
private:
	int t; //時間
};

//NFCタッチボタン関係
class TopTouchButton : public Pos{
public:
	TopTouchButton(Font *font);
	void View(double sceneOpacity); //表示
	~TopTouchButton();
private:
	MyDrawTexts *text;
	MyDrawCircle *circle;
};

#endif