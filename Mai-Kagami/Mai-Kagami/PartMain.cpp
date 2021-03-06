#include "PartMain.h"

PartMain::PartMain(Font *font, Touch *touch, Songs *songs) {
	partStart = new PartStart(font);
	partPlay = new PartPlay(font, songs, touch);
	partPause = new PartPause(font, songs, touch);
}

void PartMain::ContentLoad() {
	scene = PART_START;
	partStart->Load();
	partPlay->Load();
	partPause->Load();
}

MainSceneNum PartMain::Switch(const MainSceneNum scene) {
	switch (this->scene)
	{
	case PART_COUNTDOWN:
	case PART_PLAY:
	case PART_START:
		this->scene = partPlay->Switch(this->scene);
	case PART_PAUSE:
	case PART_SETTING:
	case PART_SETTING_PART:
	case PART_SETTING_SPEED:
	case PART_REWIND:
		this->scene = partPause->Switch(this->scene);
		break;
	}

	switch (this->scene)
	{
	case PART_NEXT:
		//Delete();
		SetDeleteFlag(TRUE);  // 削除フラグセット
		return PART_RESULT;
	case PART_BACK_SONG_SELECT:
		//Delete();
		SetDeleteFlag(TRUE);  // 削除フラグセット
		return SONG_SELECT;
	}
	return PART;
}

void PartMain::ContentUpdate() {
	if (nowScene == PART) {
		Load();
		partStart->Update(scene);
		partPlay->Update(scene);
		partPause->Update(scene);
	}
	else {
		UpdateViewFlag(FALSE);
		Delete();
	}
}

void PartMain::ContentView() {
	partPlay->View();
	partStart->View();
	partPause->View();
}

void PartMain::ContentDelete() {
	partStart->Delete();
	partPlay->Delete();
	partPause->Delete();
}

PartMain::~PartMain() {
	delete partStart;
	delete partPlay;
	delete partPause;
}