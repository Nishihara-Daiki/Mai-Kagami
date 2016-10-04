#include "Draw.h"
#include "Scene.h"

//�F�w��
Color::Color(const char *color) {
	ChangeColor(color);
}

//�F�擾
int Color::Get() {
	return c;
}

void Color::ChangeColor(const char *color) {
	if (!strcmp(color, "White"))
		c = GetColor(255, 255, 255); //���F
	else if (!strcmp(color, "Blue"))
		c = GetColor(127, 210, 234); //�F
	else if (!strcmp(color, "Black"))
		c = GetColor(0, 0, 0); //���F
	else if (!strcmp(color, "Yellow"))
		c = GetColor(255, 255, 0); //���F
}

//�\���ʒu�p�N���X�R���X�g���N�^
Pos::Pos() {
	x = 0; y = 0;
}

//�\���ʒu�p�N���X�R���X�g���N�^
Pos::Pos(const float x, const float y) {
	this->x = x / SIZE_RATE; this->y = y / SIZE_RATE;
}

//�\���ʒu�ύX
void Pos::SetPos(const float x, const float y) {
	this->x = x / SIZE_RATE; this->y = y / SIZE_RATE;
}

// SetPos()�̕ʖ�
void Pos::ChangePos(const float x, const float y) {
	SetPos(x, y);
}

void Pos::Update() {
	UpdatePosXAnimation();
	UpdatePosYAnimation();
}

void Pos::Stop(boolean jumpFlag, boolean deleteFlag) {
	PosXAnimation::Stop(jumpFlag, deleteFlag);
	PosYAnimation::Stop(jumpFlag, deleteFlag);
}


//x���W�擾
float Pos::GetX() {
	return x * SIZE_RATE;
}

//y���W�擾
float Pos::GetY() {
	return y * SIZE_RATE;
}

void Pos::SetX(const float x) {
	this->x = x / SIZE_RATE;
}

void Pos::SetY(const float y) {
	this->y = y / SIZE_RATE;
}

//�`��p�N���X�R���X�g���N�^
Draw::Draw(){}

//�`��p�N���X�R���X�g���N�^
Draw::Draw(const float x, const float y) : Pos(x, y) {}

//�`��
void Draw::View() {
	int a = (int)( alpha * (exceptFadeFlag ? 1 : gSceneSwitch.GetDrawOpacity()) );
	if (viewFlag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a); //�����x�ݒ�
		ContentView(); //���e�\��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�����x����
	}
}

void Draw::SetViewFlag(const boolean flag) {
	viewFlag = flag;
}

void Draw::SetExceptFadeFlag(const boolean flag) {
	exceptFadeFlag = flag;
}

//�����x�w��
void Draw::SetAlpha(const int alpha) {
	this->alpha = alpha;
}

int Draw::GetAlpha() {
	return alpha;
}

void Draw::Update() {
	Pos::Update();
	UpdateAlphaAnimation();
}

void Draw::Stop(boolean jumpFlag, boolean deleteFlag) {
	Pos::Stop(jumpFlag, deleteFlag);
	AlphaAnimation::Stop(jumpFlag, deleteFlag);
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