#ifndef __DRAWTEXT_H_INCLUDED__
#define __DRAWTEXT_H_INCLUDED__

#include <string.h>
#include <string>
#include "DxLib.h"
#include "Font.h"
#include "Draw.h"

//テキスト関係
class MyDrawText : public Color, public Draw2{
public:
	MyDrawText(Font *font, const char *str, const float x, const float y, const int pos, const int point, const char *colorName = "White"); // pos=左寄せ:0 / 中央寄せ:1 / 右寄せ:2
	void ContentView(); //描画
	void ChangeText(char *str); //テキスト変更
	void ChangeFont(Font *font, const int point); //フォントサイズ変更
	float GetHeight(); //縦取得
	float GetWidth(); //幅取得
protected:
	int f, point; //フォント情報、ポジション情報、フォントサイズ
	std::string s; //文字
};

//縦書きテキスト
class MyDrawTextV : public MyDrawText {
public:
	MyDrawTextV(Font *font, const char *str, const float x, const float y, const int pos, const int point, const char *colorName = "White"); // pos=左寄せ:0 / 中央寄せ:1 / 右寄せ:2
	void ContentView();
private:
	float RotCenterX;
};

//複数行のテキスト
class MyDrawTexts : public Color, public Draw {
public:
	MyDrawTexts(Font *font, const char *str, const float x, const float y, const int pos, const int point, const float lineInterval, const char *colorName = "White");
	void ContentView();
	void ChangePos(const float x, const float y);
	void ChangeText(const char *str); //テキスト変更
	float GetWidth(); //幅取得
	float GetHeight(); //高さ取得
	~MyDrawTexts();
private:
	MyDrawText *myDrawText[256];
	Font *f;
	int l = 0, p, inter, point; //行数, ポジション情報, 間隔、ポイント数
	char color[100];
};

// アンダーライン付きテキスト用アンダーライン
class MyDrawUnderLine : public Color, public Draw {
public:
	MyDrawUnderLine(const float x, const float y, const float lineLength, const float lineWidth, const char *colorName);
	void ContentView();
private:
	float w, l;  // 線の太さ、線の長さ
};

//アンダーライン付きテキスト
class MyDrawTextLine : public Color, public Draw {
public:
	MyDrawTextLine(Font *font, const char *str, const float x, const float y, const int pos, const int point, const float lineLength, const float lineWidth, const char *colorName = "White");
	void ContentView();
	void ChangePos(const float x, const float y);
	void ChangeText(char *str); //テキスト変更
	void UpdateAlphaAnimation();
	void AddMyDrawTextAlphaAnimation(double value, MyTime duration, MyTime delay = 0, Easing ease = LINER);
	void AddMyDrawUnderLineAlphaAnimation(double value, MyTime duration, MyTime delay = 0, Easing ease = LINER);
	~MyDrawTextLine();
private:
	MyDrawText *myDrawText;
	MyDrawUnderLine *myDrawUnderLine;
	int pos;
//	float x1, x2, y1, y2, w, l; //座標、線の太さ、線の長さ
	float l;
};

#endif