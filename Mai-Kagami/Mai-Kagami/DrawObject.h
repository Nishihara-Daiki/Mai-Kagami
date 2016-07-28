#ifndef __DRAWOBJECT_H_INCLUDED__
#define __DRAWOBJECT_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"
#include "Draw.h"

//線関係
class MyDrawLine {
public:
	MyDrawLine(int a, int b, int pos, int length, int width); // pos=左寄せ:0 / 中央寄せ:1 / 右寄せ:2
	void Draw();
	~MyDrawLine();
private:
	ViewPos *viewPos;
	Color *color;
	int len; //文字列の長さ
	int w;
};

//円関係
class MyDrawCircle : public Draw, public Color{
public:
	MyDrawCircle(const float x, const float y, const float radius, const char *colorName = "Blue"); //円初期化（塗りつぶしあり）
	MyDrawCircle(const float x, const float y, const float radius, const float width, const char *colorName = "Blue"); //円初期化（塗りつぶしなし）
	void View();
private:
	float r, w; //半径、線の太さ
};

//正三角形関係
class MyDrawTriangle : public Draw, public Color {
public:
	MyDrawTriangle(const float x, const float y, const float width, const int direction, const char *colorName = "Blue");
	void View(); //表示
private:
	int d;
	float w;
};

//四角形関係
class MyDrawBox : public Draw, public Color {
public:
	MyDrawBox(const float x, const float y, const float width, const float height, const char *colorName = "White"); //四角形初期化（塗りつぶしあり）
	MyDrawBox(const float x, const float y, const float width, const float height, const float line, const char *colorName = "Blue"); //四角形初期化（塗りつぶしなし）
	void View();
private:
	float w, h, l; //幅、高さ、線の太さ
};

#endif