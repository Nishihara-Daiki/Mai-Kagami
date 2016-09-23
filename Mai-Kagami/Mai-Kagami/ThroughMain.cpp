#include "ThroughMain.h"

ThroughMain::ThroughMain(Font *font, Touch *touch, Songs *songs) {
	throughStart = new ThroughStart(font);
	throughPlay = new ThroughPlay(font, songs, touch);
	throughPause = new ThroughPause(font, songs, touch);
}

void ThroughMain::ContentLoad() {
	scene = THROUGH_START;
	throughStart->Load();
	throughPlay->Load();
	throughPause->Load();
}

MainSceneNum ThroughMain::Switch(const MainSceneNum scene) {
	switch (this->scene)
	{
	case THROUGH_COUNTDOWN:
	case THROUGH_PLAY:
	case THROUGH_START:
		this->scene = throughPlay->Switch(this->scene);
	case THROUGH_PAUSE:
	case THROUGH_SETTING:
		this->scene = throughPause->Switch(this->scene);
		break;
	}

	switch (this->scene)
	{
	case THROUGH_NEXT:
		//Delete();
		SetDeleteFlag(TRUE);
		return THROUGH_RESULT;
	case THROUGH_BACK_SONG_SELECT:
		//Delete();
		SetDeleteFlag(TRUE);
		return SONG_SELECT;
	}
	return THROUGH;
}

void ThroughMain::ContentUpdate() {
	if (nowScene == THROUGH) {
		Load();
		throughStart->Update(scene);
		throughPlay->Update(scene);
		throughPause->Update(scene);
	}
	else {
		UpdateViewFlag(FALSE, SCENE_DURATION);
		Delete();
	}
}

void ThroughMain::ContentView() {
	throughPlay->View();
	throughStart->View();
	throughPause->View();
}

void ThroughMain::ContentDelete() {
	throughStart->Delete();
	throughPlay->Delete();
	throughPause->Delete();
}

ThroughMain::~ThroughMain() {
	delete throughStart;
	delete throughPlay;
	delete throughPause;
}