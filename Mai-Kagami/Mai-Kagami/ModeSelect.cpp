#include "ModeSelect.h"

//モード選択初期化
ModeSelectButton::ModeSelectButton(Font *font, Touch *touch) {
	char *through = "一曲を通して練習できます。\nあなたにあったスピードで練習でき、\n分析・採点が行われます。";
	char *part = "練習区間を設定して集中して練習でき\nます。練習途中であっても、スピード\nの変更や巻き戻しが自由にできます。";
	button[0] = new TriangleButton2(font, touch, "通し練習モード", through, 2, 0, WIDTH * 0.57, "Blue");
	button[1] = new TriangleButton2(font, touch, "部分練習モード", part, 2, 2, WIDTH * 0.57, "Yellow");
	button[2] = new CircleButton2(font, touch, "戻る", 4);
}

int ModeSelectButton::Switch(const int scene) {
	if (button[0]->GetTouch() == 1)
		return OPTION1;
	if (button[1]->GetTouch() == 1)
		return OPTION2;
	if (button[2]->GetTouch() == 1)
		return MAIN;
	return scene;
}

//モード選択ボタン計算
void ModeSelectButton::ContentUpdate() {
	if (nowScene == MODE)
		UpdateViewFlag(TRUE);
	else
		UpdateViewFlag(FALSE);
}

//モード選択ボタン表示
void ModeSelectButton::ContentView() {
	for (int i = 0; i < 3; i++)
		button[i]->View(sceneOpacity);
}

//モード選択削除
ModeSelectButton::~ModeSelectButton() {
	for (int i = 0; i < 3; i++)
		delete button[i];
}