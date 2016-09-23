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
void SubScene::UpdateViewFlag(boolean flag, long duration, long wait) {
	boolean isFirstTime = FALSE;	// (待ち時間前の)1ループ目かどうか
	boolean isInterrupt = FALSE;	// フェード終了前に次のフェードが入ってるのかどうか
	boolean isWaited = FALSE;		// 待ち時間終了時ループかどうか
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
	//	//if (viewFlag != flag) {  // 待ち終了前に次のフェードが入った場合
	//	//	waitCount = wait;
	//	//	return;
	//	//}
	//	waitCount--;
	//	if (waitCount == 0) {
	//		fadeStatus = NOT_FADE;
	//		IsFirstTime = TRUE;	// 待ち終了、即ち、フェードイン・アウトの1ループ目
	//	}
	//	else {
	//		return;
	//	}
	//}
	//printfDx("%d", fadeStatus);
	if (viewFlag != flag && fadeStatus == NOT_FADE) {	// 1ループ目
		isFirstTime = TRUE;
		fadeStatus = FADE_WAIT;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// フェード終了前に次のフェードが入った場合の1ループ目
		isFirstTime = TRUE;
		isInterrupt = TRUE;
	}
	if (fadeCount == duration || isFirstTime && wait == 0) {  // 待ち終了
		isWaited = TRUE;
		fadeStatus = flag ? FADING_IN : FADING_OUT;
	}

	if (duration == 0 && isWaited) {	// 間隔がゼロの時は一気にワープ
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
	//if (isWated) {	// 1フレーム目ならば
	//	if(isInterrupt == FALSE)	// 割り込みじゃなければ
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