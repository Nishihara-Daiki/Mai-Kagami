#include "Scene.h"

SceneSwitch gSceneSwitch;


//表示中かどうか確認する(TRUE:表示中、FALSE：非表示中)
boolean ViewFlag::CheckView() {
	return viewFlag;
}

// セットしたいフラグとそれに変更するまでの遅延フレーム数
void ViewFlag::UpdateViewFlag(boolean flag, long wait, long duration) {
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
			viewFlag = flag;
			sceneOpacity = 1;
			fadeStatus = NOT_FADE;
		}
	}
	SetOpacity();
}

boolean ViewFlag::GetViewFlag() {
	return viewFlag;
}

long ViewFlag::GetFadeCount() {
	return fadeCount;
}

double ViewFlag::GetSceneOpacity() {
	return sceneOpacity;
}


//計算
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

//表示
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


//ロード
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

		/* ここでスレッド立てる */

		loadStatus = THREADING;
		cnt = 0;
	}
	if (loadStatus == THREADING) {
		if (TRUE) {				// スレッド終了していたら(今はスレッドないのでTRUEにしてる)
			ContentLoad();		// 画像のロードを開始して
			loadStatus = LOADING;	// 状態更新
		}
		else {
			cnt++;
		}
	}
	if (loadStatus == LOADING) {
		if (GetASyncLoadNum() == 0) {	// 画像ロードが終われば
			loadStatus = LOADED;
		}
		cnt++;
	}
}

//削除
void MainScene::Delete() {
	if(deleteFlag == TRUE) {
		if (GetFadeCount() == 0) {
			ContentDelete();
			loadStatus = UNLOADED;
			deleteFlag = FALSE;
		}
	}
}

void MainScene::SetDeleteFlag(boolean flag) {
	deleteFlag = flag;
}