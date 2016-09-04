#include "PartResult.h"

PartResult::PartResult(Font *font, Songs *songs, Touch *touch) {
	this->songs = songs;
	this->font = font;
	title = new MyDrawTextLine(font, "Ì“_Œ‹‰Ê", WIDTH * 0.5, HEIGHT * 0.15, 1, 60, WIDTH * 0.5, 4);
	button = new CircleButton2(font, touch, "ŽŸ‚Ö", 4);
}

void PartResult::Load() {
	song = songs->GetSong(songs->GetNowSong());
	song->coverGraph->Load();
	song->coverGraph->ChangePos(WIDTH * 0.3, HEIGHT * 0.26);
	song->drawSongTitle->ChangePos(WIDTH * 0.6, HEIGHT * 0.24);
	partMax = song->GetPartNum();
	for (int i = 0; i < partMax; i++) {
		SongPart *songPart = song->GetPart(i);
		float y = HEIGHT * 0.35 + HEIGHT * 0.35 * i / (partMax - 1);
		part[i] = new MyDrawText(font, songPart->GetName(), WIDTH * 0.27, y, 1, 30);
		circle[i] = new MyDrawCircle(WIDTH * 0.42, y, 16, "Blue");
		char str[256];
		sprintf_s(str, sizeof(str), "~%1.1lf", song->danceMovie->GetSpeed());
		speed[i] = new MyDrawText(font, str, WIDTH * 0.62, y, 1, 30);
		score[i] = new MyDrawText(font, "A", WIDTH * 0.77, y, 1, 30);
		if (i < song->StartPart() || i > song->EndPart()) {
			part[i]->SetAlpha(100);
			circle[i]->ChangeColor("White");
			circle[i]->SetAlpha(100);
			speed[i]->ChangeText("-");
			speed[i]->SetAlpha(100);
			score[i]->ChangeText("-");
			score[i]->SetAlpha(100);
		}
	}
}

int PartResult::Switch(const int scene) {
	if (button->GetTouch() == 1)
		return PART_RESULT_FINISH;
	return scene;
}

void PartResult::ContentUpdate() {
	if (nowScene == PART_RESULT_TOP || nowScene == PART_RESULT_FINISH)
		viewFlag = TRUE;
	else
		viewFlag = FALSE;
}

void PartResult::ContentView() {
	title->View();
	button->View();
	song->coverGraph->View();
	song->drawSongTitle->View();
	for (int i = 0; i < partMax; i++) {
		part[i]->View();
		circle[i]->View();
		speed[i]->View();
		score[i]->View();
	}
}

PartResult::~PartResult() {
	delete title;
	delete button;
	for (int i = 0; i < partMax; i++) {
		delete part[i];
		delete circle[i];
		delete speed[i];
		delete score[i];
	}
}

PartFinish::PartFinish(Font *font, Touch *touch) {
	blackBox = new BlackBox();
	button[0] = new CircleButton(font, touch, "‚à‚¤ˆê“x", 0, WIDTH * 0.75, "White");
	button[1] = new CircleButton(font, touch, "•”•ª—ûK", 1, WIDTH * 0.75, "White");
	button[2] = new CircleButton(font, touch, "’Ê‚µ—ûK", 2, WIDTH * 0.75, "White");
	button[3] = new CircleButton(font, touch, "‹È‘I‘ð‰æ–Ê", 3, WIDTH * 0.75, "White");
}

int PartFinish::Switch(const int scene) {
	if (button[0]->GetTouch() == 1)
		return PART_RESULT_BACK_PLAY;
	if (button[1]->GetTouch() == 1)
		return PART_RESULT_BACK_PART_OPTION;
	if (button[2]->GetTouch() == 1)
		return PART_RESULT_BACK_THROUGH_OPTION;
	if (button[3]->GetTouch() == 1)
		return PART_RESULT_BACK_SONG_SELECT;
	return scene;
}

void PartFinish::ContentUpdate() {
	if (nowScene == PART_RESULT_FINISH)
		viewFlag = TRUE;
	else
		viewFlag = FALSE;
}

void PartFinish::ContentView() {
	blackBox->View();
	for (int i = 0; i < 4; i++)
		button[i]->View();
}

PartFinish::~PartFinish() {
	delete blackBox;
	for (int i = 0; i < 4; i++)
		delete button[i];
}