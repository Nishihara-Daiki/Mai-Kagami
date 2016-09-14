#include "Top.h"

//�g�b�v���S
TopLogo::TopLogo(const float y, const double* sceneOpacity)
	: MyDrawGraph(WIDTH * 0.5, y, "img/logo.png", sceneOpacity) {
}

//NFC�^�b�`���b�Z�[�W�R���X�g���N�^
TopTouchMessage::TopTouchMessage(Font *font, const float y, const double* sceneOpacity)
	: MyDrawText(font, "-�J�[�h���^�b�`���Ă�������-", WIDTH * 0.5, y, 1, 46, sceneOpacity) {
	Init(); //������
}

//NFC�^�b�`���b�Z�[�W������
void TopTouchMessage::Init() {
	t = 0;
}

//NFC�^�b�`���b�Z�[�W�v�Z
void TopTouchMessage::Update() {
	if (t > 180)
		SetAlpha(0);
	else if (t > 120)
		SetAlpha((180 - t) * 255 / 60);
	else if (t > 60)
		SetAlpha(255);
	else
		SetAlpha(t * 255 / 60);
	t++;
	t %= 240;
}

//NFC�^�b�`���b�Z�[�W�\��
void TopTouchMessage::View() {
	MyDrawText::View(); //�����\��
}

//NFC�^�b�`�{�^���R���X�g���N�^
TopTouchButton::TopTouchButton(Font *font, const double* sceneOpacity)
	: Pos(WIDTH, NFC_POS) {
	float r = WIDTH / 12;
	text = new MyDrawTexts(font, "������\n�^�b�`�I", GetX() - r, GetY(), 2, 40, 20, sceneOpacity);
	circle = new MyDrawCircle(GetX(), GetY(), r, sceneOpacity);
}

//NFC�^�b�`�{�^���\��
void TopTouchButton::View() {
	text->View(); //�~�\��
	circle->View(); //�e�L�X�g�\��
}

TopTouchButton::~TopTouchButton() {
	delete text;
	delete circle;
}