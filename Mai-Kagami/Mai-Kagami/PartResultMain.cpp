#include "PartResultMain.h"

PartResultMain::PartResultMain(Font *font, Touch *touch, Songs *songs) {
	partResult = new PartResult(font, songs, touch);
	partFinish = new PartFinish(font, touch);
}

void PartResultMain::ContentLoad() {
	scene = PART_RESULT_TOP;
	partResult->Load();
	partFinish->Load();
}

MainScene PartResultMain::Switch(const MainScene scene) {
	switch (this->scene)
	{
	case PART_RESULT_TOP:
		this->scene = partResult->Switch(this->scene);
		break;
	case PART_RESULT_FINISH:
		this->scene = partFinish->Switch(this->scene);
		break;
	}
	if (this->scene == PART_RESULT_BACK_PLAY) {
		Delete();
		return PART;
	}
	if (this->scene == PART_RESULT_BACK_SONG_SELECT) {
		Delete();
		return SONG_SELECT;
	}
	if (this->scene == PART_RESULT_BACK_THROUGH_OPTION) {
		Delete();
		return THROUGH_OPTION;
	}
	if (this->scene == PART_RESULT_BACK_PART_OPTION) {
		Delete();
		return PART_OPTION;
	}
	return PART_RESULT;
}

void PartResultMain::ContentUpdate() {
	if (nowScene == PART_RESULT) {
		Load();
		partResult->Update(scene);
		partFinish->Update(scene);
	}
}

void PartResultMain::ContentView() {
	partResult->View();
	partFinish->View();
}

void PartResultMain::ContentDelete() {
	partResult->Delete();
	partFinish->Delete();
}

PartResultMain::~PartResultMain() {
	delete partResult;
	delete partFinish;
}