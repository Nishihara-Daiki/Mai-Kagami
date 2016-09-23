#include "Scene.h"

SceneSwitch gSceneSwitch;

//計算
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

// セットしたいフラグとそれに変更するまでの遅延フレーム数
void Scene::UpdateViewFlag(boolean flag, long duration, long wait) {
	boolean isFirstTime = FALSE;	// (待ち時間前の)1ループ目かどうか
	boolean isWaited = FALSE;		// 待ち時間終了時ループかどうか
	
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// 1ループ目
		isFirstTime = TRUE;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// フェード終了前に次のフェードが入った場合の1ループ目
		isFirstTime = TRUE;
	}
	if (fadeStatus == FADE_WAIT && viewFlag == flag) {
		isFirstTime = TRUE;
	}
	if (fadeCount == duration || isFirstTime && wait == 0) {  // 待ち終了
		isWaited = TRUE;
		fadeStatus = flag ? FADING_IN : FADING_OUT;
	}
	if (duration == 0 && isWaited) {	// 間隔がゼロの時は一気にワープ
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

//表示
void Scene::View() {
//	gSceneSwitch.SetOpacity(sceneOpacity);
	SetOpacity(sceneOpacity);
	if (viewFlag)
		ContentView();
}

//表示中かどうか確認する(TRUE:表示中、FALSE：非表示中)
boolean Scene::CheckView() {
	return viewFlag;
}

void SubScene::SetOpacity(double opacity) {
	gSceneSwitch.SetSubOpacity(opacity);
}

void MainScene::SetOpacity(double opacity) {
	gSceneSwitch.SetMainOpacity(opacity);
}

//ロード
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

//削除
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