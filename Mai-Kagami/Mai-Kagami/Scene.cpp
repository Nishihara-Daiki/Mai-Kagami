#include "Scene.h"

SceneSwitch gSceneSwitch;

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
void SubScene::UpdateViewFlag(boolean flag, long duration) {
	boolean IsFirstTime = FALSE;	// ���񂩂ǂ���
	boolean IsInterrupt = FALSE;	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h�������Ă�̂��ǂ���
	//double sceneOpacity = gSceneSwitch.GetOpacity();
	//if(this->delay > 0)
	//	printfDx("%3d", this->delay);
	//if (flag == TRUE)
	//	delay = 0;
	//fadeStatus = flag ? FADING_IN : FADING_OUT;
	//if (viewFlag == flag) {
		//delayCount = 0;
		//delay = 0;
		//fadeStatus = NOT_FADE;
		//return;
	//}
	//if (viewFlag != flag) {
	//	fadeStatus = flag ? FADING_IN : FADING_OUT;
	//}
	if (duration == 0) {
		fadeStatus = NOT_FADE;
		viewFlag = flag;
		sceneOpacity = 1.0;
		return;
	}
	if (viewFlag != flag && fadeStatus == NOT_FADE) { // �t�F�[�h�C���E�A�E�g��1���[�v��
		IsFirstTime = TRUE;
		//sceneOpacity = 1.0;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h���������ꍇ��1���[�v��
		IsFirstTime = TRUE;
		IsInterrupt = TRUE;
	}

	if (IsFirstTime) {
		delayCount = duration;
		//printfDx("0");
	}

//	if (fadeStatus == NOT_FADE) {
//		if (delayCount == delay && (sceneOpacity == 1.0 || sceneOpacity == 0) && delay != 0) // 1�t���[���ڂȂ��
	if (IsFirstTime) {
		fadeStatus = flag ? FADING_IN : FADING_OUT;
		viewFlag = TRUE;
	}
//		else
//			return;
//	}
	//if (fadeStatus == FADING_IN)
	//	viewFlag = TRUE;
	//if (fadeStatus == FADING_OUT)
	//	viewFlag = TRUE;

	if (flag == TRUE)
		sceneOpacity = 1 - sceneOpacity;
	if (IsFirstTime) {	// 1�t���[���ڂȂ��
		if(IsInterrupt == FALSE)	// ���荞�݂���Ȃ����
			sceneOpacity = 1.0;
	}
	else {
		if (IsFirstTime)
			sceneOpacity = 1.0;
		else
			sceneOpacity *= (double)delayCount / (delayCount + 1);
	}
	if (flag == TRUE)
		sceneOpacity = 1 - sceneOpacity;

	//sceneOpacity = 0.5;
	//if(sceneOpacity != 0.0 && sceneOpacity != 1.0)
	//	printfDx("%0.1f  ", sceneOpacity);
	//sceneOpacity = 0.5;

	if (delayCount > 0) {
		delayCount--;
		if (delayCount == 0) {
			viewFlag = flag;
			sceneOpacity = 1;
			fadeStatus = NOT_FADE;
		}
	}
	//gSceneSwitch.FadeStatus(fadeStatus);
	gSceneSwitch.SetOpacity(sceneOpacity);
}

//�\��
void SubScene::View() {
	//gSceneSwitch.FadeStatus(fadeStatus);
	gSceneSwitch.SetOpacity(sceneOpacity);
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