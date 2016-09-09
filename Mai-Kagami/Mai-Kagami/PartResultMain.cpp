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

	switch(this->scene) {
	case PART_RESULT_BACK_PLAY:
		//Delete();
		SetDeleteFlag(TRUE);
		return PART;
	case PART_RESULT_BACK_SONG_SELECT:
		//Delete();
		SetDeleteFlag(TRUE);
		return SONG_SELECT;
	case PART_RESULT_BACK_THROUGH_OPTION:
		//Delete();
		SetDeleteFlag(TRUE);
		return THROUGH_OPTION;
	case PART_RESULT_BACK_PART_OPTION:
		//Delete();
		SetDeleteFlag(TRUE);
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
	else {
		UpdateViewFlag(FALSE, SCENE_DELAY);
		Delete();
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