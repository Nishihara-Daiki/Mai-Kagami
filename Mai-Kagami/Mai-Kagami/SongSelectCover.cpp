#include "SongSelectCover.h"
#include "Animation.h"

SongSelectCover::SongSelectCover(Font *font, Song *song, const int now)
	: Song(*song) {
	char *folder = "";
	SetNow(now);
}

void SongSelectCover::Load(int max) {
	danceMovie->ChangePos(WIDTH * 0.5, HEIGHT * 0.57);
	danceMovie->ChangeEx(0.5);
	coverGraph->Load();
	coverWhite->Load();
	Change(0, max);

	coverGraph->ChangePos(WIDTH * 0.5, CalcY());
	coverGraph->SetAlpha(CalcAlpha());
	coverGraph->ChangeEx(CalcEx());
	coverWhite->ChangePos(WIDTH * 0.5, CalcY());
	coverWhite->SetAlpha(CalcAlphaWhite());
	coverWhite->ChangeEx(CalcEx());
	playFlag = FALSE;
}

void SongSelectCover::Release() {
	coverGraph->Release();
	coverWhite->Release();
}

//表示位置の計算
void SongSelectCover::Update(int num, int max) {
	//static int t = 0;	// 邪魔 Jaity
	Change(num, max);
	int n = GetNow();
	const int duration = 10;
	float y = CalcY();

	if (num) {
		coverGraph->PosXAnimation::Add(WIDTH * 0.5,	duration, 0, Easing::EaseOut_SINE);
		coverWhite->PosXAnimation::Add(WIDTH * 0.5,	duration, 0, Easing::EaseOut_SINE);
		coverGraph->PosYAnimation::Add(y,			duration, 0, Easing::EaseOut_SINE);
		coverWhite->PosYAnimation::Add(y,			duration, 0, Easing::EaseOut_SINE);

		coverGraph->AlphaAnimation::Add(CalcAlpha(), duration, 0, Easing::EaseOut_SINE);
		coverWhite->AlphaAnimation::Add(CalcAlphaWhite(), duration, 0, Easing::EaseOut_SINE);
		coverGraph->ExAnimation::Add(CalcEx(), duration, 0, Easing::EaseOut_SINE);
		coverWhite->ExAnimation::Add(CalcEx(), duration, 0, Easing::EaseOut_SINE);
	}
	if (n == -2 && num > 0 || n == max - 3 && num < 0) {
		coverGraph->Stop(TRUE, TRUE);
		coverWhite->Stop(TRUE, TRUE);
		coverGraph->PosXAnimation::Add(WIDTH * 0.5, 0);
		coverWhite->PosXAnimation::Add(WIDTH * 0.5, 0);
		coverGraph->PosYAnimation::Add(y, 0);
		coverWhite->PosYAnimation::Add(y, 0);
	}

	coverGraph->Update(); // アニメーション更新
	coverWhite->Update();
}

void SongSelectCover::Draw(int scene) {
	int n = GetNow();
	if (n <= 6) {	// 移動中を考えて 5 も描画
		coverWhite->View();
		coverGraph->View();
	}
	switch (scene) {
	case OPTION1:
		if (playFlag)
			StopMusic();
		playFlag = FALSE;
		danceMovie->Start();
		danceMovie->View();
		break;
	case OPTION2:
		if (playFlag)
			StopMusic();
		playFlag = FALSE;
		break;
	default:
		if (n == 0 && !playFlag) {
			//			PlayMusic(music, DX_PLAYTYPE_LOOP); // 重いので一時的に消去 Jaity
			playFlag = TRUE;
		}
		else if (n != 0) {
			playFlag = FALSE;
		}
		break;
	}
}

//曲の位置IDを変更
void SongSelectCover::Change(int num, int max) {
	int n = GetNow();
	n = (n + num + max + 2) % max - 2;
	SetNow(n);
}

// y座標を算出して取得
float SongSelectCover::CalcY() {
	int n = GetNow();
	float y;

	n = n < 6 ? n : 6;

	if (n <= -1)
		y = HEIGHT * 0.35 - 30 + 150 * n;
	else if (n == 0)
		y = HEIGHT * 0.35;
	else
		y = HEIGHT * 0.35 + 30 + 150 * n;

	return y;
}

int SongSelectCover::CalcAlpha() {
	return GetNow() ? 180 : 255;
}

int SongSelectCover::CalcAlphaWhite() {
	return GetNow() ? 0 : 255;
}

double SongSelectCover::CalcEx() {
	return GetNow() ? 0.7 : 1.0;
}
