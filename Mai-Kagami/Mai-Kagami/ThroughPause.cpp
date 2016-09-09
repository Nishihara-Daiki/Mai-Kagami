#include "ThroughPause.h"

ThroughPauseButton::ThroughPauseButton(Touch *touch) {
	pauseButton = new CircleGraphButton(touch, 0, "img/pause.png");
}

void ThroughPauseButton::Load() {
	pauseButton->Load();
}

int ThroughPauseButton::Switch(const int scene) {
	if (pauseButton->GetTouch() == 1)
		return THROUGH_PAUSE;
	return scene;
}

void ThroughPauseButton::ContentUpdate() {
	switch (nowScene)
	{
	case THROUGH_PLAY:
	case THROUGH_COUNTDOWN:
	case THROUGH_START:
		UpdateViewFlag(TRUE);
		break;
	default:
		UpdateViewFlag(FALSE);
		break;
	}
}

void ThroughPauseButton::ContentView() {
	pauseButton->View();
}

void ThroughPauseButton::Delete() {
	pauseButton->Release();
}

ThroughPauseButton::~ThroughPauseButton() {
	delete pauseButton;
}

ThroughPauseScreen::ThroughPauseScreen(Font *font, Songs *songs, Touch *touch) 
	: PauseScreen(font, songs, touch, THROUGH_PAUSE, THROUGH_START, THROUGH_BACK_SONG_SELECT, THROUGH_SETTING) {}

int ThroughPauseSetting::Switch(const int scene) {
	if (button->GetTouch() == 1) {
		song->danceMovie->SetSpeed();
		return THROUGH_PAUSE;
	}
	return scene;
}

void ThroughPauseSetting::ContentUpdate() {
	if (nowScene == THROUGH_SETTING) {
		SpeedPop::ContentUpdate();
		UpdateViewFlag(TRUE);
	}
	else {
		UpdateViewFlag(FALSE);
	}
}

ThroughPause::ThroughPause(Font *font, Songs *songs, Touch *touch) {
	throughPauseButton = new ThroughPauseButton(touch); //ポーズボタン画面
	throughPauseScreen = new ThroughPauseScreen(font, songs, touch);
	throughPauseSetting = new ThroughPauseSetting(font, songs, touch);
	flag = FALSE;
}

void ThroughPause::Load() {
	throughPauseButton->Load();
	throughPauseScreen->Load();
	throughPauseSetting->Load();
}

int ThroughPause::Switch(const int scene) {
	switch (scene)
	{
	case THROUGH_COUNTDOWN:
	case THROUGH_PLAY:
	case THROUGH_START:
		return throughPauseButton->Switch(scene);
	case THROUGH_PAUSE:
		return throughPauseScreen->Switch(scene);
	case THROUGH_SETTING:
		return throughPauseSetting->Switch(scene);
	}
	return scene;
}

void ThroughPause::ContentUpdate() {
	throughPauseButton->Update(nowScene);
	throughPauseScreen->Update(nowScene);
	throughPauseSetting->Update(nowScene);

	switch (nowScene)
	{
	case THROUGH_SETTING:
	case THROUGH_PLAY:
	case THROUGH_PAUSE:
	case THROUGH_COUNTDOWN:
	case THROUGH_START:
		UpdateViewFlag(TRUE);
		break;
	default:
		UpdateViewFlag(FALSE);
		break;
	}
}

void ThroughPause::ContentView() {
	throughPauseButton->View();
	throughPauseScreen->View();
	throughPauseSetting->View();
}

void ThroughPause::Delete() {
	throughPauseButton->Delete();
	throughPauseScreen->Delete();
	throughPauseSetting->Delete();
}

ThroughPause::~ThroughPause() {
	delete throughPauseButton;
	delete throughPauseScreen;
	delete throughPauseSetting;
}