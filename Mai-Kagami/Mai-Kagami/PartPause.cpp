#include "PartPause.h"

PartPauseButton::PartPauseButton(Touch *touch, Songs *songs) {
	this->songs = songs;
	button[0] = new CircleGraphButton(touch, 0, "img/pause.png");
	button[1] = new CircleGraphButton(touch, 2, "img/pause.png");
}

void PartPauseButton::Load() {
	for(int i = 0; i < 2; i++)
		button[i]->Load();
}

int PartPauseButton::Switch(const int scene) {
	static int lastScene = PART_START;
	if (button[0]->GetTouch() == 1)
		return PART_PAUSE;
	if (button[1]->GetTouch() > 0)
		return PART_REWIND;
	if (scene == PART_REWIND)
		return lastScene;
	lastScene = scene;
	return scene;
}

void PartPauseButton::ContentUpdate() {
	Song *song = songs->GetSong(songs->GetNowSong());
	if (button[1]->GetTouch() > 0 && nowScene == PART_REWIND) {
		if(song->danceMovie->GetStartFlame() <= song->danceMovie->GetNowFlame())
			song->danceMovie->Seek(song->danceMovie->GetNowFlame()-5);
	}

	switch (nowScene)
	{
	case PART_PLAY:
	case PART_COUNTDOWN:
	case PART_START:
	case PART_REWIND:
		viewFlag = TRUE;
		break;
	default:
		viewFlag = FALSE;
		break;
	}
}

void PartPauseButton::ContentView() {
	for (int i = 0; i < 2; i++)
		button[i]->View();
}

void PartPauseButton::Delete() {
	for (int i = 0; i < 2; i++)
		button[i]->Release();
}

PartPauseButton::~PartPauseButton() {
	for (int i = 0; i < 2; i++)
		delete button[i];
}

PartPauseScreen::PartPauseScreen(Font *font, Songs *songs, Touch *touch)
	: PauseScreen(font, songs, touch, PART_PAUSE, PART_START, PART_BACK_SONG_SELECT, PART_SETTING) {}

PartOptionPreview3::PartOptionPreview3(Font *font, Songs *songs, Touch *touch)
	: PartOptionPreview(font, songs, touch, PART_SETTING, PART_SETTING_PART, PART_SETTING_SPEED) {
	button = new CircleButton2(font, touch, "戻る", 4);
	blackBox = new BlackBox();
}

int PartOptionPreview3::Switch(const int scene) {
	if (button->GetTouch() == 1)
		return PART_PAUSE;
	return PartOptionPreview::Switch(scene);
}

void PartOptionPreview3::ContentView() {
	blackBox->View();
	button->View();
	PartOptionPreview::ContentView();
}

PartOptionPreview3::~PartOptionPreview3() {
	delete button;
	delete blackBox;
}

PartPauseSetting::PartPauseSetting(Font *font, Songs *songs, Touch *touch)
	: PartOptionPop(font, songs, touch, PART_SETTING, PART_SETTING_PART, PART_SETTING_SPEED, new PartOptionPreview3(font, songs, touch)) {}

PartPause::PartPause(Font *font, Songs *songs, Touch *touch) {
	partPauseButton = new PartPauseButton(touch, songs); //ポーズボタン画面
	partPauseScreen = new PartPauseScreen(font, songs, touch);
	partPauseSetting = new PartPauseSetting(font, songs, touch);
	flag = FALSE;
}

void PartPause::Load() {
	partPauseButton->Load();
	partPauseScreen->Load();
	partPauseSetting->Load();
}

int PartPause::Switch(const int scene) {
	switch (scene)
	{
	case PART_COUNTDOWN:
	case PART_PLAY:
	case PART_START:
	case PART_REWIND:
		return partPauseButton->Switch(scene);
	case PART_PAUSE:
		return partPauseScreen->Switch(scene);
	case PART_SETTING:
	case PART_SETTING_PART:
	case PART_SETTING_SPEED:
		return partPauseSetting->Switch(scene);
	}
	return scene;
}

void PartPause::ContentUpdate() {
	partPauseButton->Update(nowScene);
	partPauseScreen->Update(nowScene);
	partPauseSetting->Update(nowScene);

	switch (nowScene)
	{
	case PART_SETTING:
	case PART_PLAY:
	case PART_PAUSE:
	case PART_SETTING_PART:
	case PART_SETTING_SPEED:
	case PART_COUNTDOWN:
	case PART_REWIND:
	case PART_START:
		viewFlag = TRUE;
		break;
	default:
		viewFlag = FALSE;
		break;
	}
}

void PartPause::ContentView() {
	partPauseButton->View();
	partPauseScreen->View();
	partPauseSetting->View();
}

void PartPause::Delete() {
	partPauseButton->Delete();
	partPauseScreen->Delete();
	partPauseSetting->Delete();
}

PartPause::~PartPause() {
	delete partPauseButton;
	delete partPauseScreen;
	delete partPauseSetting;
}