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
void SubScene::UpdateViewFlag(boolean flag, long duration, long wait) {
	boolean isFirstTime = FALSE;	// (�҂����ԑO��)1���[�v�ڂ��ǂ���
	boolean isInterrupt = FALSE;	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h�������Ă�̂��ǂ���
	boolean isWaited = FALSE;		// �҂����ԏI�������[�v���ǂ���
	//static long waitCount = 0;

	//switch (fadeStatus) {
	//case NOT_FADE:
	//	if (viewFlag != flag) {
	//		waitCount = wait;
	//		if (wait > 0) {
	//			fadeStatus = FADE_WAIT;
	//			return;
	//		}
	//	}
	//	break;
	//case FADE_WAIT:
	//	//if (viewFlag != flag) {  // �҂��I���O�Ɏ��̃t�F�[�h���������ꍇ
	//	//	waitCount = wait;
	//	//	return;
	//	//}
	//	waitCount--;
	//	if (waitCount == 0) {
	//		fadeStatus = NOT_FADE;
	//		IsFirstTime = TRUE;	// �҂��I���A�����A�t�F�[�h�C���E�A�E�g��1���[�v��
	//	}
	//	else {
	//		return;
	//	}
	//}
	//printfDx("%d", fadeStatus);
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// 1���[�v��
		isFirstTime = TRUE;
		fadeStatus = FADE_WAIT;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h���������ꍇ��1���[�v��
		isFirstTime = TRUE;
		isInterrupt = TRUE;
	}
	if (fadeCount == duration || isFirstTime && wait == 0) {  // �҂��I��
		isWaited = TRUE;
		fadeStatus = flag ? FADING_IN : FADING_OUT;
	}

	if (duration == 0 && isWaited) {	// �Ԋu���[���̎��͈�C�Ƀ��[�v
		fadeStatus = NOT_FADE;
		viewFlag = flag;
		sceneOpacity = 1.0;
		return;
	}

	if (isFirstTime)
		fadeCount = duration + wait;

	if (fadeStatus == FADE_WAIT) {
		fadeCount--;
		return;
	}

	if (isWaited)
		viewFlag = TRUE;

	//if (flag == TRUE)
	//	sceneOpacity = 1 - sceneOpacity;
	//if (isWated) {	// 1�t���[���ڂȂ��
	//	if(isInterrupt == FALSE)	// ���荞�݂���Ȃ����
	//		sceneOpacity = 1.0;
	//}
	//else {
	//	//if (isFirstTime)
	//	//	sceneOpacity = 1.0;
	//	//else
	//	long count = fadeCount - wait;
	//	sceneOpacity *= (double)count / (count + 1);
	//}
	//if (flag == TRUE)
	//	sceneOpacity = 1 - sceneOpacity;

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