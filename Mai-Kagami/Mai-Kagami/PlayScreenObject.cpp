#include "PlayScreenObject.h"

//進捗バー
PlayBar::PlayBar(Font *font, const double* sceneOpacity) {
	barAll = new MyDrawBar(WIDTH * 0.41, HEIGHT * 0.055, WIDTH * 0.56, 10, sceneOpacity);
	barNow = new MyDrawBar(WIDTH * 0.41, HEIGHT * 0.055, 0, 10, sceneOpacity, "Blue");
	circle[0] = new MyDrawCircle(WIDTH * 0.41, HEIGHT * 0.055, 12, sceneOpacity);
	circle[1] = new MyDrawCircle(WIDTH * 0.41, HEIGHT * 0.055, 5, sceneOpacity, "White");
	this->font = font;
	this->sceneOpacity = sceneOpacity;
}

void PlayBar::Load(Song *song) {
	this->song = song;
	song->LoadPart();
}

void PlayBar::Update() {
	int nowFlame = song->danceMovie->GetNowFlame();
	int startFlame = song->danceMovie->GetStartFlame();
	int lastFlame = song->danceMovie->GetEndFlame();

	for (int i = 0; i < song->GetPartNum(); i++) {
		SongPart *songPart = song->GetPart(i);
		float x = WIDTH * 0.41 + WIDTH * 0.56 * (float)(songPart->GetFlame() - startFlame) / (lastFlame - startFlame);
		part[i] = new MyDrawTextV(font, songPart->GetName(), x, HEIGHT * 0.056, 0, 16, sceneOpacity);
		if (songPart->GetFlame() >= startFlame && songPart->GetFlame() <= lastFlame)
			part[i]->SetViewFlag(TRUE);
		else
			part[i]->SetViewFlag(FALSE);
	}

	float now = WIDTH * 0.56 * (float)(nowFlame - startFlame) / (lastFlame - startFlame);
	barNow->ChangeSize(now, 10);
	for (int i = 0; i < 2; i++)
		circle[i]->ChangePos(WIDTH * 0.41 + now, HEIGHT * 0.055);
	for (int i = song->GetPartNum() - 1; i >= 0; i--) {
		SongPart *songPart = song->GetPart(i);
		if (nowFlame < lastFlame && nowFlame >= songPart->GetFlame()) {
			part[i]->ChangeColor("Blue");
			part[i]->ChangeFont(font, 20);
		}
		else {
			part[i]->ChangeColor("White");
			part[i]->ChangeFont(font, 16);
		}
		lastFlame = songPart->GetFlame();
	}
}

void PlayBar::View() {
	barAll->View();
	barNow->View();
	for (int i = 0; i < 2; i++)
		circle[i]->View();
	for (int i = 0; i < song->GetPartNum(); i++)
		part[i]->View();
}

PlayBar::~PlayBar() {
	delete barAll;
	delete barNow;
	for (int i = 0; i < 2; i++)
		delete circle[i];
}

//カウントダウン画面再生三角形
PlayTriangle::PlayTriangle(const float x, const float y, const double* sceneOpacity)
	: MyDrawTriangle(sceneOpacity, "Yellow") {
	const float w = 100, ex = 12;
	float x1 = x - w + ex, x2 = x - w + ex, x3 = x + w + ex;
	float y1 = y + w, y2 = y - w, y3 = y;
	ChangePos(x1, y1, x2, y2, x3, y3);
}

//カウントダウン画面
CountDown::CountDown(Font *font, const int thisScene, const int playScene) {
	this->thisScene = thisScene;
	this->playScene = playScene;
	const float x = WIDTH * 0.5; //円の中心（x座標）
	const float y = HEIGHT * 0.5; //円の中心（y座標）
	const float r = WIDTH * 0.2; //円の半径
	text = new MyDrawText(font, "準備をしてください", x, y + r + 80, 1, 40, &sceneOpacity);
	circle = new MyDrawCircle(x, y, r, 3, &sceneOpacity, "White"); //縁が白色の円
	countCircle1 = new MyDrawCircleGauge(x, y, r, 0, 5, &sceneOpacity, "Blue");	//ゲージ
	countCircle2 = new MyDrawCircle(0, 0, 12, &sceneOpacity, "Blue");	//ゲージの先の円
}

int CountDown::Switch(const int scene) {
	if (++count == max)
		return playScene;
	return scene;
}

void CountDown::ContentUpdate() {
	if (nowScene == thisScene) {
		UpdateViewFlag(TRUE);
		countCircle1->ChangeDegree((double)count / max * 100);
		countCircle2->ChangePos(countCircle1->GetEndX() * SIZE_RATE, countCircle1->GetEndY() * SIZE_RATE);
	}
	else {
		count = 0;
		UpdateViewFlag(FALSE);
	}
}

void CountDown::ContentView() {
	text->View();
	circle->View();
	countCircle1->View();
	countCircle2->View();
}

CountDown::~CountDown() {
	delete text;
	delete circle;
	delete countCircle1;
	delete countCircle2;
}