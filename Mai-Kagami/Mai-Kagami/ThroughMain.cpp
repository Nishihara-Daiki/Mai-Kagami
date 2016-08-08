#include "ThroughMain.h"

ThroughMain::ThroughMain(Font *font, Touch *touch, Songs *songs) {
	f = font;
	ThroughMain::songs = songs;
	loadFlag = 0;
	throughStart = new ThroughStart(f);
	throughPlay = new ThroughPlay(f);
	throughPause = new ThroughPause(f);
	scene = THROUGH_START;
	ThroughMain::touch = touch;
}

void ThroughMain::Load() {
	if (loadFlag == 2)
		return;

	if (loadFlag == 0 && GetASyncLoadNum() == 0) {
		throughPlay->Load(songs->GetSong(songs->GetNowSong()));
		throughPause->Load();
		loadFlag = 1;
	}

	if (loadFlag == 1 && GetASyncLoadNum() == 0)
		loadFlag = 2;
}

int ThroughMain::Update() {
	Load();

	if (loadFlag == 2) {
		switch (scene)
		{
		case THROUGH_PAUSE:
			if (touch->Get(0) == 1)
				scene = THROUGH_START;
			break;
		default:
			KinectDistance kinectDistance;
			if (kinectDistance.CheckDistance() == TRUE)
				scene = THROUGH_PLAY;
			else
				scene = THROUGH_START;
			if (touch->Get(0) == 1)
				scene = THROUGH_PAUSE;
		}
		throughPlay->Update(scene);
		throughStart->Update(scene);
		throughPause->Update(scene);
	}
	return THROUGH;
}

void ThroughMain::View() {
	if (loadFlag == 2) {
		throughPlay->View();
		switch (scene)
		{
		case THROUGH_START:
			throughStart->View();
			break;
		}
		throughPause->View();
	}
}

void ThroughMain::Delete() {
	loadFlag = 0;
}

ThroughMain::~ThroughMain() {

}