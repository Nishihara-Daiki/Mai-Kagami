#include "Scene.h"

SceneSwitch gSceneSwitch;

//計算
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

// セットしたいフラグとそれに変更するまでの遅延フレーム数
void SubScene::UpdateViewFlag(boolean flag, long duration) {
	boolean IsFirstTime = FALSE;	// 初回かどうか
	boolean IsInterrupt = FALSE;	// フェード終了前に次のフェードが入ってるのかどうか

	if (duration == 0) {	// 間隔がゼロの時は一気にワープ
		fadeStatus = NOT_FADE;
		viewFlag = flag;
		sceneOpacity = 1.0;
		return;
	}
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// フェードイン・アウトの1ループ目
		IsFirstTime = TRUE;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// フェード終了前に次のフェードが入った場合の1ループ目
		IsFirstTime = TRUE;
		IsInterrupt = TRUE;
	}

	if (IsFirstTime) {
		delayCount = duration;
	}

	if (IsFirstTime) {
		fadeStatus = flag ? FADING_IN : FADING_OUT;
		viewFlag = TRUE;
	}

	if (flag == TRUE)
		sceneOpacity = 1 - sceneOpacity;
	if (IsFirstTime) {	// 1フレーム目ならば
		if(IsInterrupt == FALSE)	// 割り込みじゃなければ
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

	if (delayCount > 0) {
		delayCount--;
		if (delayCount == 0) {
			viewFlag = flag;
			sceneOpacity = 1;
			fadeStatus = NOT_FADE;
		}
	}
	gSceneSwitch.SetOpacity(sceneOpacity);
}

//表示
void SubScene::View() {
	gSceneSwitch.SetOpacity(sceneOpacity);
	if (viewFlag)
		ContentView();
}

//表示中かどうか確認する(TRUE:表示中、FALSE：非表示中)
boolean SubScene::CheckView() {
	return viewFlag;
}

//ロード
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

//削除
void Scene::Delete() {
	if(deleteFlag == TRUE) {
		if (delayCount == 0) {
			ContentDelete();
			loadFlag = 0;
			deleteFlag = FALSE;
		}
	}
}

void Scene::SetDeleteFlag(boolean flag) {
	deleteFlag = flag;
}