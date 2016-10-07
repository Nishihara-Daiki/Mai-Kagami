#include "Scene.h"

SceneSwitch gSceneSwitch;


//�\�������ǂ����m�F����(TRUE:�\�����AFALSE�F��\����)
boolean ViewFlag::CheckView() {
	return viewFlag;
}

// �Z�b�g�������t���O�Ƃ���ɕύX����܂ł̒x���t���[����
void ViewFlag::UpdateViewFlag(boolean flag, long wait, long duration) {
	boolean isFirstTime = FALSE;	// (�҂����ԑO��)1���[�v�ڂ��ǂ���
	boolean isWaited = FALSE;		// �҂����ԏI�������[�v���ǂ���

	if (fadeStatus == FADE_END) {
		viewFlag = flag;
		sceneOpacity = 1;
		fadeStatus = NOT_FADE;
		isFadeEnd = TRUE;
		return;
	}
	isFadeEnd = FALSE;
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// 1���[�v��
		isFirstTime = TRUE;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// �t�F�[�h�I���O�Ɏ��̃t�F�[�h���������ꍇ��1���[�v��
		isFirstTime = TRUE;
	}
	if (fadeStatus == FADE_WAIT && viewFlag == flag) {
		isFirstTime = TRUE;
	}
	if (!isFirstTime && fadeCount == duration || isFirstTime && wait == 0) {  // �҂��I��
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
		if (!isWaited)
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
			fadeStatus = FADE_END;
		}
	}
	SetOpacity();
}

boolean ViewFlag::GetViewFlag() {
	return viewFlag;
}

boolean ViewFlag::IsFadeEnd() {
	return isFadeEnd;
}

double ViewFlag::GetSceneOpacity() {
	return sceneOpacity;
}


//�v�Z
void Scene::Update(const int scene) {
	nowScene = scene;
	ContentUpdate();
}

void Scene::Load() {
	UpdateViewFlag(TRUE, 0, 0);
}

void Scene::Delete() {
	UpdateViewFlag(FALSE, 0, 0);
}

//�\��
void Scene::View() {
	SetOpacity();
	if (GetViewFlag())
		ContentView();
}


void SubScene::SetOpacity() {
	gSceneSwitch.SetSubOpacity(GetSceneOpacity());
}

void MainScene::SetOpacity() {
	gSceneSwitch.SetMainOpacity(GetSceneOpacity());
}


//���[�h
void MainScene::Load() {
	static int cnt = 0;
	if (loadStatus == LOADED) {
		int wait = SCENE_IN_WAIT - cnt;
		if(wait < 0)
			wait = 0;
		UpdateViewFlag(TRUE, wait);
		return;
	}

	if (loadStatus == UNLOADED) {

		/* �����ŃX���b�h���Ă� */

		loadStatus = THREADING;
		cnt = 0;
	}
	if (loadStatus == THREADING) {
		if (TRUE) {				// �X���b�h�I�����Ă�����(���̓X���b�h�Ȃ��̂�TRUE�ɂ��Ă�)
			ContentLoad();		// �摜�̃��[�h���J�n����
			loadStatus = LOADING;	// ��ԍX�V
		}
		else {
			cnt++;
		}
	}
	if (loadStatus == LOADING) {
		if (GetASyncLoadNum() == 0) {	// �摜���[�h���I����
			loadStatus = LOADED;
		}
		cnt++;
	}
}

//�폜
void MainScene::Delete() {
	if(deleteFlag == TRUE) {
		if (IsFadeEnd()) {
			ContentDelete();
			loadStatus = UNLOADED;
			deleteFlag = FALSE;
		}
	}
}

void MainScene::SetDeleteFlag(boolean flag) {
	deleteFlag = flag;
}