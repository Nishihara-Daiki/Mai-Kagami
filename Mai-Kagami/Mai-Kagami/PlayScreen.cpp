#include "PlayScreen.h"

PlayScreen::PlayScreen(Font *font, Songs *songs, Touch *touch, const int startScene, const int countDownScene, const int playScene, const int finishScene) {
	this->startScene = startScene;
	this->countDownScene = countDownScene;
	this->playScene = playScene;
	this->finishScene = finishScene;
	this->songs = songs;
	playBar = new PlayBar(font);
	countDown = new CountDown(font, countDownScene, playScene);
}

void PlayScreen::Load() {
	song = songs->GetSong(songs->GetNowSong());
	song->danceMovie->ChangeEx(1.2);
	song->danceMovie->ChangePos(WIDTH * 0.5, HEIGHT * 0.5);
	song->danceMovie->Seek();
	song->drawSongTitle->ChangePos(WIDTH * 0.2, HEIGHT * 0.03);
	playBar->Load(song);
	viewFlag = TRUE;
}

int PlayScreen::Switch(const int scene) {
	KinectDistance kinectDistance;

	if (kinectDistance.CheckDistance() == FALSE) //ƒ†[ƒU‚ª2m‚æ‚è‹ß‚©‚Á‚½‚ç
		return startScene;
	else if (scene == startScene)
		return countDownScene;
	else if (scene == countDownScene)
		return countDown->Switch(scene);
	else if (scene == playScene) {
		if (song->danceMovie->GetNowFlame() == song->danceMovie->GetEndFlame()) {
			song->danceMovie->Stop();
			return finishScene;
		}
	}
	return scene;
}

void PlayScreen::ContentUpdate() {
	playBar->Update();
	countDown->Update(nowScene);

	if (nowScene == playScene)
		song->danceMovie->Start();
	else
		song->danceMovie->Stop();
}

void PlayScreen::ContentView() {
	song->danceMovie->View();
	song->drawSongTitle->View();
	playBar->View();
	countDown->View();
}

PlayScreen::~PlayScreen() {
	delete playBar;
	delete countDown;
}