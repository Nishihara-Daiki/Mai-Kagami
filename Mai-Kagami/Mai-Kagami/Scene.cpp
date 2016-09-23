#include "Scene.h"

SceneSwitch gSceneSwitch;

//�v�Z
void Scene::Update(const int scene) {
	nowScene = scene;
	ContentUpdate();
}

void Scene::Load() {
	viewFlag = TRUE;
}

void Scene::Delete() {
	viewFlag = FALSE;
}

// �Z�b�g�������t���O�Ƃ���ɕύX����܂ł̒x���t���[����
void Scene::UpdateViewFlag(boolean flag, long duration, long wait) {
	boolean isFirstTime = FALSE;	// (�҂����ԑO��)1���[�v�ڂ��ǂ���
	boolean isWaited = FALSE;		// �҂����ԏI�������[�v���ǂ���
	
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// 1���[�v��
		isFirstTime = TRUE;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h���������ꍇ��1���[�v��
		isFirstTime = TRUE;
	}
	if (fadeStatus == FADE_WAIT && viewFlag == flag) {
		isFirstTime = TRUE;
	}
	if (fadeCount == duration || isFirstTime && wait == 0) {  // �҂��I��
		isWaited = TRUE;
		fadeStatus = flag ? FADING_IN : FADING_OUT;
	}
	if (duration == 0 && isWaited) {	// �Ԋu���[���̎��͈�C�Ƀ��[�v
		fadeStatus = NOT_FADE;
		viewFlag = flag;
		sceneOpacity = 1.0;
		fadeCount = 0;
		return;
	}
	if (isFirstTime) {
		fadeCount = duration + wait;
		fadeStatus = FADE_WAIT;
	}


	if (fadeStatus == FADE_WAIT) {
		fadeCount--;
		return;
	}

	if (isWaited)
		viewFlag = TRUE;

	if (fadeStatus == FADING_IN || fadeStatus == FADING_OUT) {
		sceneOpacity = (double)fadeCount / duration;
		if (fadeStatus == FADING_IN)
			sceneOpacity = 1 - sceneOpacity;
	}

	if (fadeCount > 0) {
		fadeCount--;
		if (fadeCount == 0) {
			viewFlag = flag;
			sceneOpacity = 1;
			fadeStatus = NOT_FADE;
		}
	}
//	gSceneSwitch.SetOpacity(sceneOpacity);
	SetOpacity(sceneOpacity);
}

//�\��
void Scene::View() {
//	gSceneSwitch.SetOpacity(sceneOpacity);
	SetOpacity(sceneOpacity);
	if (viewFlag)
		ContentView();
}

//�\�������ǂ����m�F����(TRUE:�\�����AFALSE�F��\����)
boolean Scene::CheckView() {
	return viewFlag;
}

void SubScene::SetOpacity(double opacity) {
	gSceneSwitch.SetSubOpacity(opacity);
}

void MainScene::SetOpacity(double opacity) {
	gSceneSwitch.SetMainOpacity(opacity);
}

//���[�h
void MainScene::Load() {
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
void MainScene::Delete() {
	if(deleteFlag == TRUE) {
		if (fadeCount == 0) {
			ContentDelete();
			loadFlag = 0;
			deleteFlag = FALSE;
		}
	}
}

void MainScene::SetDeleteFlag(boolean flag) {
	deleteFlag = flag;
}