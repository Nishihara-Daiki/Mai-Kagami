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
}

// �Z�b�g�������t���O�Ƃ���ɕύX����܂ł̒x���t���[����
void SubScene::UpdateViewFlag(boolean flag, long duration, long delay) {
	boolean IsFirstTime = FALSE;	// ���񂩂ǂ���
	boolean IsInterrupt = FALSE;	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h�������Ă�̂��ǂ���

	if (duration == 0) {	// �Ԋu���[���̎��͈�C�Ƀ��[�v
		fadeStatus = NOT_FADE;
		viewFlag = flag;
		sceneOpacity = 1.0;
		return;
	}
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// �t�F�[�h�C���E�A�E�g��1���[�v��
		IsFirstTime = TRUE;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h���������ꍇ��1���[�v��
		IsFirstTime = TRUE;
		IsInterrupt = TRUE;
	}

	if (IsFirstTime) {
		fadeCount = duration;
	}

	if (IsFirstTime) {
		fadeStatus = flag ? FADING_IN : FADING_OUT;
		viewFlag = TRUE;
	}

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
			sceneOpacity *= (double)fadeCount / (fadeCount + 1);
	}
	if (flag == TRUE)
		sceneOpacity = 1 - sceneOpacity;

	if (fadeCount > 0) {
		fadeCount--;
		if (fadeCount == 0) {
			viewFlag = flag;
			sceneOpacity = 1;
			fadeStatus = NOT_FADE;
		}
	}
	gSceneSwitch.SetOpacity(sceneOpacity);
}

//�\��
void SubScene::View() {
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
void Scene::Delete() {
	if(deleteFlag == TRUE) {
		if (fadeCount == 0) {
			ContentDelete();
			loadFlag = 0;
			deleteFlag = FALSE;
		}
	}
}

void Scene::SetDeleteFlag(boolean flag) {
	deleteFlag = flag;
}