#include "Button.h"

//ボタン
Button::Button(const int num, Touch *touch)
	: Draw(0, BUTTON_POS + num * BUTTON_INTERVAL) {
	this->num = num;
	this->touch = touch;
}

int Button::GetTouch() {
	return touch->Get(num);
}

//三角形のボタン
TriangleButton::TriangleButton(Font *font, Touch *touch, const char *str, const int direction, const int num, char *colorName)
	: Button(num, touch) {
	text = new MyDrawText(font, str, WIDTH * 0.94, GetY(), 2, 30);
	myDrawTriangle2 = new MyDrawTriangle2(WIDTH * 0.97, GetY(), WIDTH * 0.03, direction, colorName);
}

void TriangleButton::ContentView(double opacity) {
	myDrawTriangle2->View(opacity);
	text->View(opacity);
}

TriangleButton::~TriangleButton() {
	delete myDrawTriangle2;
	delete text;
}

//説明文付き三角形のボタン
TriangleButton2::TriangleButton2(Font *font, Touch *touch, const char *title, const char *str, const int direction, const int num, const float x, const char *colorName)
	: Button(num, touch) {
	float pos = GetY();
	text = new MyDrawText(font, title, x, pos - HEIGHT * 0.03, 0, 30, colorName);
	descriptionText = new MyDrawTexts(font, str, x, pos + HEIGHT * 0.01, 0, 20, 15);

	float width = WIDTH * 0.35;
	myDrawBox = new MyDrawBox(x + width / 2, pos, width + WIDTH * 0.05, HEIGHT * 0.09, 2, colorName);
	myDrawTriangle2 = new MyDrawTriangle2(WIDTH * 0.97, pos, WIDTH * 0.03, direction, colorName);
}

void TriangleButton2::ContentView(double opacity) {
	descriptionText->View(opacity);
	myDrawBox->View(opacity);
	myDrawTriangle2->View(opacity);
	text->View(opacity);
}

TriangleButton2::~TriangleButton2() {
	delete myDrawTriangle2;
	delete myDrawBox;
	delete descriptionText;
	delete text;
}


//文字右寄せボタン
CircleButton::CircleButton(Font *font, Touch *touch, const char *str, const int num, char *colorName) 
	: Button(num, touch) {
	text = new MyDrawText(font, str, WIDTH * 0.94, GetY(), 2, 30);
	myDrawCircle = new MyDrawCircle(WIDTH * 0.97, GetY(), WIDTH * 0.015, 7, colorName);
}

//文字中央寄せボタン
CircleButton::CircleButton(Font *font, Touch *touch, const char *str, const int num, const float x, char *colorName)
	: Button(num, touch) {
	text = new MyDrawText(font, str, x, GetY(), 1, 30);
	myDrawCircle = new MyDrawCircle(WIDTH * 0.97, GetY(), WIDTH * 0.015, 7, colorName);
}

void CircleButton::ContentView(double opacity) {
	myDrawCircle->View(opacity);
	text->View(opacity);
}

CircleButton::~CircleButton() {
	delete text;
	delete myDrawCircle;
}

//文字が丸の中にあるボタン
CircleButton2::CircleButton2(Font *font, Touch *touch, const char *str, const int num, char *colorName)
	: Button(num, touch) {
	float r = WIDTH * 0.045;
	float x = WIDTH - r - 4;
	text = new MyDrawText(font, str, x, GetY(), 1, 30, "Black");
	myDrawCircle = new MyDrawCircle(x, GetY(), r, colorName);
}

void CircleButton2::ContentView(double opacity) {
	myDrawCircle->View(opacity);
	text->View(opacity);
}

CircleButton2::~CircleButton2() {
	delete text;
	delete myDrawCircle;
}

//画像付きのボタン
CircleGraphButton::CircleGraphButton(Touch *touch, const int num, const char *fileName) 
	: Button(num, touch) {
	float r = WIDTH * 0.075;
	myDrawCircle = new MyDrawCircle(WIDTH, GetY(), r);
	myDrawGraph = new MyDrawGraph(WIDTH  - 35, GetY(), fileName);
}

void CircleGraphButton::Load() {
	myDrawGraph->Load();
}

void CircleGraphButton::ContentView(double opacity) {
	myDrawCircle->View(opacity);
	myDrawGraph->View(opacity);
}

void CircleGraphButton::Release() {
	myDrawGraph->Release();
}

CircleGraphButton::~CircleGraphButton() {
	delete myDrawCircle;
	delete myDrawGraph;
}

//画像、テキスト付きのボタン
CircleGraphTextButton::CircleGraphTextButton(Font *font, Touch *touch, const char *str, const int num, const char *fileName)
	: Button(num, touch) {
	float x = WIDTH * 0.965;
	float y = GetY();
	float r = WIDTH * 0.026;
	text = new MyDrawText(font, str, x - r - 12, y, 2, 30);
	myDrawCircle = new MyDrawCircle(x, y, r, "Blue");
	myDrawGraph = new MyDrawGraph(x, y, fileName, 0.6);
}

void CircleGraphTextButton::Load() {
	myDrawGraph->Load();
}

void CircleGraphTextButton::ContentView(double opacity) {
	text->View(opacity);
	myDrawCircle->View(opacity);
	myDrawGraph->View(opacity);
}

void CircleGraphTextButton::Release() {
	myDrawGraph->Release();
}

CircleGraphTextButton::~CircleGraphTextButton() {
	delete text;
	delete myDrawCircle;
	delete myDrawGraph;
}