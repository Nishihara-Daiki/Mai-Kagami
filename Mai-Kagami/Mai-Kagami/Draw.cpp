#include "Draw.h"

//色指定
Color::Color(const char *color) {
	ChangeColor(color);
}

//色取得
int Color::Get() {
	return c;
}

void Color::ChangeColor(const char *color) {
	if (!strcmp(color, "White"))
		c = GetColor(255, 255, 255); //白色
	else if (!strcmp(color, "Blue"))
		c = GetColor(127, 210, 234); //青色
	else if (!strcmp(color, "Black"))
		c = GetColor(0, 0, 0); //黒色
	else if (!strcmp(color, "Yellow"))
		c = GetColor(255, 255, 0); //黄色
}

//表示位置用クラスコンストラクタ
Pos::Pos() {
	x = 0; y = 0;
}

//表示位置用クラスコンストラクタ
Pos::Pos(const float x, const float y) {
	this->x = x / SIZE_RATE; this->y = y / SIZE_RATE;
}

//表示位置変更
void Pos::ChangePos(const float x, const float y) {
	this->x = x / SIZE_RATE; this->y = y / SIZE_RATE;
}

// アニメーション用パラメータセット Jaity
void Pos::SetPosAnimation(float target_x, float target_y, Easing ease) {
	if (GetTime() != 0)
		return;
	default_x = GetX();
	default_y = GetY();
	this->target_x = target_x;
	this->target_y = target_y;
	ease_pos = ease;
//	SetRate(duration, ease);
	//SetDuration(duration);
}


// アニメーション更新 Jaity
void Pos::Update() {
	double r = UpdateRate(ease_pos);
	float nx = default_x + (target_x - default_x) * r;
	float ny = default_y + (target_y - default_y) * r;
	ChangePos(nx, ny);
}

// アニメーション中断
// 中断時に最終値に飛ぶかどうか
void Pos::Stop(boolean jumpF) {
	if (jumpF == TRUE)
		SetAnimationTime(0);
	Update();
	Reset();
}

//x座標取得
float Pos::GetX() {
	return x * SIZE_RATE;
}

//y座標取得
float Pos::GetY() {
	return y * SIZE_RATE;
}

//描画用クラスコンストラクタ
Draw::Draw(){}

//描画用クラスコンストラクタ
Draw::Draw(const float x, const float y) : Pos(x, y) {}

//描画
void Draw::View() {
	if (viewFlag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //透明度設定
		ContentView(); //内容表示
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透明度解除
	}
}

void Draw::SetViewFlag(const boolean flag) {
	viewFlag = flag;
}

//透明度指定
void Draw::SetAlpha(const int alpha) {
	this->alpha = alpha;
}

int Draw::GetAlpha() {
	return alpha;
}

void Draw::SetAlphaAnimation(int target_alpha, Easing ease) {
	if (GetTime() != 0)
		return;
	default_alpha = GetAlpha();
	this->target_alpha= target_alpha;
	ease_alpha = ease;
}

void Draw::Update() {
	double r = UpdateRate(ease_alpha);
	int na = default_alpha + (target_alpha - default_alpha) * r;
	SetAlpha(na);
	Pos::Update();
}

void Draw::Stop(boolean jumpF) {
	if (jumpF == TRUE)
		SetAnimationTime(0);
	Update();
	Reset();
}

Draw2::Draw2(const int pos) {
	p = pos;
}

Draw2::Draw2(const float x, const float y, const int pos) {
	p = pos;
	ChangePos(x, y);
}

void Draw2::ChangePos() {
	float a = 0;
	switch (p) {
	case 1:
		a -= GetWidth() / 2;
		break;
	case 2:
		a -= GetWidth();
		break;
	}

	Draw::ChangePos(xx + a, yy - GetHeight() / 2);
}

void Draw2::ChangePos(const float x, const float y) {
	xx = x;
	yy = y;
	Draw2::ChangePos();
}

float Draw2::GetX() {
	return xx;
}

float Draw2::GetY() {
	return yy;
}