#include "Scene.h"

//�v�Z
void SubScene::Update(const int scene) {
	nowScene = scene;
	ContentUpdate();
}

void SubScene::Load() {
	viewFlag = TRUE;
}

void SubScene::Delete() {
	viewFlag = FALSE;
//	printfDx("Del");
}

// �Z�b�g�������t���O�Ƃ���ɕύX����܂ł̒x���t���[����
void SubScene::UpdateViewFlag(boolean flag, long delay) {
	//if(this->delay > 0)
	//	printfDx("%3d", this->delay);
	//if (flag == TRUE)
	//	delay = 0;
	if (viewFlag == flag) {
		//delayCount = 0;
		//delay = 0;
		return;
	}
	if (delayCount == 0)
		delayCount = delay;
	if (delay == 0)
		viewFlag = flag;

	//if (flag == TRUE)
	//	sceneOpacity = 1 - sceneOpacity;
	//if (delayCount == delay && sceneOpacity == 1.0 && delay != 0) { // 1�t���[���ڂȂ��
	//	sceneOpacity = 1.0;
	//}
	//else {
	//	sceneOpacity *= (double)delayCount / (delayCount + 1);
	//}
	//if (flag == TRUE)
	//	sceneOpacity = 1 - sceneOpacity;

	//sceneOpacity = 0.5;
	//if(sceneOpacity != 0.0 && sceneOpacity != 1.0)
	//	printfDx("%0.1f  ", sceneOpacity);
	sceneOpacity = 1;

	if (delayCount > 0) {
		delayCount--;
		if (delayCount == 0) {
			viewFlag = flag;
			sceneOpacity = 1;
		}
	}
}

//�\��
void SubScene::View() {
	if (viewFlag)
		ContentView();
}

//�\�������ǂ����m�F����(TRUE:�\�����AFALSE�F��\����)
boolean SubScene::CheckView() {
	return viewFlag;
}

//���[�h
void Scene::Load() {
	if (loadFlag == 2)
		return;

	if (loadFlag == 0) {
		ContentLoad();
		loadFlag = 1;
	}

	if (loadFlag == 1 && GetASyncLoadNum() == 0) {
		UpdateViewFlag(TRUE, 0);
		loadFlag = 2;
	}
}

//�폜
//void Scene::Delete() {
//	ContentDelete();
//	UpdateViewFlag(FALSE);
//	loadFlag = 0;
//}

//�폜
void Scene::Delete() {
//	static int count = 0;
//	printfDx("%2d", deleteFlag);
	if(deleteFlag == TRUE) {
		//if (count++ == SCENE_DELAY) {
		//	ContentDelete();
		//	//viewFlag = FALSE;
		//	UpdateViewFlag(FALSE, 0);
		//	loadFlag = 0;
		//	deleteFlag = FALSE;
		//	count = 0;
		//}
		if (delayCount == 0) {
			ContentDelete();
			//viewFlag = FALSE;
			//UpdateViewFlag(FALSE, 0);
			loadFlag = 0;
			deleteFlag = FALSE;
		}
	}
}

void Scene::SetDeleteFlag(boolean flag) {
	deleteFlag = flag;
}