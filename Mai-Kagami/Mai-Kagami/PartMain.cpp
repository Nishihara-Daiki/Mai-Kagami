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

MainScene PartMain::Switch(const MainScene scene) {
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
		Delete();
		return PART_RESULT;
	case PART_BACK_SONG_SELECT:
		Delete();
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