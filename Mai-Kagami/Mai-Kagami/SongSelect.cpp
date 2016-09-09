#include "SongSelect.h"

//曲選択画面ボタン初期化
SongSelectButton::SongSelectButton(Font *font, Touch *touch) {
	button[0] = new TriangleButton(font, touch, "前の曲へ", 0, 0);
	button[1] = new CircleButton(font, touch, "決定", 1);
	button[2] = new TriangleButton(font, touch, "次の曲へ", 1, 2);
	button[3] = new CircleButton2(font, touch, "終了", 4);
}

//曲選択画面ボタン画面切り替え
int SongSelectButton::Switch(const int scene) {
	if (button[1]->GetTouch() == 1)
		return MODE;
	if (button[3]->GetTouch() == 1)
		return BACK;
	return scene;
}

//曲選択画面ボタン計算
void SongSelectButton::ContentUpdate() {
	if (nowScene == MAIN)
		UpdateViewFlag(TRUE);
	else
		UpdateViewFlag(FALSE);
}

//曲選択画面ボタン表示
void SongSelectButton::ContentView() {
	for (int i = 0; i < 4; i++)
		button[i]->View();
}

SongSelectButton::~SongSelectButton() {
	for (int i = 0; i < 4; i++)
		delete button[i];
}

//終了用ポップアップ
SongSelectPop::SongSelectPop(Font *font, Touch *touch) {
	this->touch = touch;
	blackBox = new BlackBox();
	title = new MyDrawText(font, "- 終了 -", WIDTH * 0.75, HEIGHT * 0.4, 1, 40, "Blue");
	message = new MyDrawText(font, "本当に終了\nしますか？", WIDTH * 0.75, HEIGHT * 0.45, 1, 30);
	button[0] = new CircleButton(font, touch, "はい", 1, WIDTH * 0.75, "White");
	button[1] = new CircleButton(font, touch, "いいえ", 2, WIDTH * 0.75, "White");
}

int SongSelectPop::Switch(const int scene) {
	if (touch->Get(1) == 1)
		return BACK_TOP;
	if (touch->Get(2) == 1)
		return MAIN;
	return scene;
}

void SongSelectPop::ContentUpdate() {
	if (nowScene == BACK)
		UpdateViewFlag(TRUE);
	else
		UpdateViewFlag(FALSE);
}

void SongSelectPop::ContentView() {
	blackBox->View();
	title->View();
	message->View();
	for (int i = 0; i < 2; i++)
		button[i]->View();
}

SongSelectPop::~SongSelectPop() {
	delete blackBox;
	delete title;
	delete message;
	for (int i = 0; i < 2; i++)
		delete button[i];
}