#include "ThroughResultMain.h"

ThroughResultMain::ThroughResultMain(Font *font, Touch *touch, Songs *songs) {
	throughResult = new ThroughResult(font, songs, touch);
	throughDetail = new ThroughDetail(font, songs, touch);
}

void ThroughResultMain::ContentLoad() {
	scene = THROUGH_RESULT_TOP;
	throughResult->Load();
	throughDetail->Load();
}

MainSceneNum ThroughResultMain::Switch(const MainSceneNum scene) {
	switch (this->scene)
	{
	case THROUGH_RESULT_TOP:
		this->scene = throughResult->Switch(this->scene);
		break;
	case THROUGH_RESULT_DETAIL:
	case THROUGH_RESULT_FINISH:
		this->scene = throughDetail->Switch(this->scene);
		break;
	}

	switch (this->scene) {
	case THROUGH_RESULT_BACK_PLAY:
		//Delete();
		SetDeleteFlag(TRUE);
		return THROUGH;
	case THROUGH_RESULT_BACK_SONG_SELECT:
		//Delete();
		SetDeleteFlag(TRUE);
		return SONG_SELECT;
	case THROUGH_RESULT_BACK_PART_OPTION:
		//Delete();
		SetDeleteFlag(TRUE);
		return PART_OPTION;
	}
	return THROUGH_RESULT;
}

void ThroughResultMain::ContentUpdate() {
	if (nowScene == THROUGH_RESULT) {
		Load();
		throughResult->Update(scene);
		throughDetail->Update(scene);
	}
	else {
		UpdateViewFlag(FALSE);
		Delete();
	}
}

void ThroughResultMain::ContentView() {
	throughResult->View();
	throughDetail->View();
}

void ThroughResultMain::ContentDelete() {
	throughResult->Delete();
	throughDetail->Delete();
}

ThroughResultMain::~ThroughResultMain() {
	delete throughResult;
	delete throughDetail;
}