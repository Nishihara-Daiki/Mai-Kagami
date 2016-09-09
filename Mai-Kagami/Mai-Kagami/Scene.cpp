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
	if (flag == TRUE)
		delay = 0;
	if (viewFlag == flag)
		return;
	if (this->delay == 0)
		this->delay = delay;
	if (delay == 0)
		viewFlag = flag;
	if (this->delay > 0) {
		this->delay--;
		if (this->delay == 0)
			viewFlag = flag;
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
		UpdateViewFlag(TRUE);
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
		if (delay == 0) {
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