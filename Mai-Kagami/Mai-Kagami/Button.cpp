#include "Button.h"

//ボタン
Button::Button(const int num, Touch *touch, const double* sceneOpacity)
	: Draw(0, BUTTON_POS + num * BUTTON_INTERVAL, sceneOpacity) {
	this->num = num;
	this->touch = touch;
}

int Button::GetTouch() {
	return touch->Get(num);
}

//三角形のボタン
TriangleButton::TriangleButton(Font *font, Touch *touch, const char *str, const int direction, const int num, const double* sceneOpacity, char *colorName)
	: Button(num, touch, sceneOpacity) {
	text = new MyDrawText(font, str, WIDTH * 0.94, GetY(), 2, 30, sceneOpacity);
	myDrawTriangle2 = new MyDrawTriangle2(WIDTH * 0.97, GetY(), WIDTH * 0.03, direction, sceneOpacity, colorName);
}

void TriangleButton::ContentView() {
	myDrawTriangle2->View();
	text->View();
}

TriangleButton::~TriangleButton() {
	delete myDrawTriangle2;
	delete text;
}

//説明文付き三角形のボタン
TriangleButton2::TriangleButton2(Font *font, Touch *touch, const char *title, const char *str, const int direction, const int num, const float x, const double* sceneOpacity, const char *colorName)
	: Button(num, touch, sceneOpacity) {
	float pos = GetY();
	text = new MyDrawText(font, title, x, pos - HEIGHT * 0.03, 0, 30, sceneOpacity, colorName);
	descriptionText = new MyDrawTexts(font, str, x, pos + HEIGHT * 0.01, 0, 20, 15, sceneOpacity);

	float width = WIDTH * 0.35;
	myDrawBox = new MyDrawBox(x + width / 2, pos, width + WIDTH * 0.05, HEIGHT * 0.09, 2, sceneOpacity, colorName);
	myDrawTriangle2 = new MyDrawTriangle2(WIDTH * 0.97, pos, WIDTH * 0.03, direction, sceneOpacity, colorName);
}

void TriangleButton2::ContentView() {
	descriptionText->View();
	myDrawBox->View();
	myDrawTriangle2->View();
	text->View();
}

TriangleButton2::~TriangleButton2() {
	delete myDrawTriangle2;
	delete myDrawBox;
	delete descriptionText;
	delete text;
}


//文字右寄せボタン
CircleButton::CircleButton(Font *font, Touch *touch, const char *str, const int num, const double* sceneOpacity, char *colorName)
	: Button(num, touch, sceneOpacity) {
	text = new MyDrawText(font, str, WIDTH * 0.94, GetY(), 2, 30, sceneOpacity);
	myDrawCircle = new MyDrawCircle(WIDTH * 0.97, GetY(), WIDTH * 0.015, 7, sceneOpacity, colorName);
}

//文字中央寄せボタン
CircleButton::CircleButton(Font *font, Touch *touch, const char *str, const int num, const float x, const double* sceneOpacity, char *colorName)
	: Button(num, touch, sceneOpacity) {
	text = new MyDrawText(font, str, x, GetY(), 1, 30, sceneOpacity);
	myDrawCircle = new MyDrawCircle(WIDTH * 0.97, GetY(), WIDTH * 0.015, 7, sceneOpacity, colorName);
}

void CircleButton::ContentView() {
	myDrawCircle->View();
	text->View();
}

CircleButton::~CircleButton() {
	delete text;
	delete myDrawCircle;
}

//文字が丸の中にあるボタン
CircleButton2::CircleButton2(Font *font, Touch *touch, const char *str, const int num, const double* sceneOpacity, char *colorName)
	: Button(num, touch, sceneOpacity) {
	float r = WIDTH * 0.045;
	float x = WIDTH - r - 4;
	text = new MyDrawText(font, str, x, GetY(), 1, 30, sceneOpacity, "Black");
	myDrawCircle = new MyDrawCircle(x, GetY(), r, sceneOpacity, colorName);
}

void CircleButton2::ContentView() {
	myDrawCircle->View();
	text->View();
}

CircleButton2::~CircleButton2() {
	delete text;
	delete myDrawCircle;
}

//画像付きのボタン
CircleGraphButton::CircleGraphButton(Touch *touch, const int num, const char *fileName, const double* sceneOpacity)
	: Button(num, touch, sceneOpacity) {
	float r = WIDTH * 0.075;
	myDrawCircle = new MyDrawCircle(WIDTH, GetY(), r, sceneOpacity);
	myDrawGraph = new MyDrawGraph(WIDTH  - 35, GetY(), fileName, sceneOpacity);
}

void CircleGraphButton::Load() {
	myDrawGraph->Load();
}

void CircleGraphButton::ContentView() {
	myDrawCircle->View();
	myDrawGraph->View();
}

void CircleGraphButton::Release() {
	myDrawGraph->Release();
}

CircleGraphButton::~CircleGraphButton() {
	delete myDrawCircle;
	delete myDrawGraph;
}

//画像、テキスト付きのボタン
CircleGraphTextButton::CircleGraphTextButton(Font *font, Touch *touch, const char *str, const int num, const char *fileName, const double* sceneOpacity)
	: Button(num, touch, sceneOpacity) {
	float x = WIDTH * 0.965;
	float y = GetY();
	float r = WIDTH * 0.026;
	text = new MyDrawText(font, str, x - r - 12, y, 2, 30, sceneOpacity);
	myDrawCircle = new MyDrawCircle(x, y, r, sceneOpacity, "Blue");
	myDrawGraph = new MyDrawGraph(x, y, fileName, sceneOpacity, 0.6);
}

void CircleGraphTextButton::Load() {
	myDrawGraph->Load();
}

void CircleGraphTextButton::ContentView() {
	text->View();
	myDrawCircle->View();
	myDrawGraph->View();
}

void CircleGraphTextButton::Release() {
	myDrawGraph->Release();
}

CircleGraphTextButton::~CircleGraphTextButton() {
	delete text;
	delete myDrawCircle;
	delete myDrawGraph;
}