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
//	printfDx("Del");
}

// セットしたいフラグとそれに変更するまでの遅延フレーム数
void SubScene::UpdateViewFlag(boolean flag, long duration) {
	boolean IsFirstTime = FALSE;	// 初回かどうか
	boolean IsInterrupt = FALSE;	// フェード終了前に次のフェードが入ってるのかどうか
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
	if (viewFlag != flag && fadeStatus == NOT_FADE) { // フェードイン・アウトの1ループ目
		IsFirstTime = TRUE;
		//sceneOpacity = 1.0;
	}
	if (fadeStatus == FADING_IN && !flag || fadeStatus == FADING_OUT && flag) {	// フェード終了前に次のフェードが入った場合の1ループ目
		IsFirstTime = TRUE;
		IsInterrupt = TRUE;
	}

	if (IsFirstTime) {
		delayCount = duration;
		//printfDx("0");
	}

//	if (fadeStatus == NOT_FADE) {
//		if (delayCount == delay && (sceneOpacity == 1.0 || sceneOpacity == 0) && delay != 0) // 1フレーム目ならば
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

//表示
void SubScene::View() {
	//gSceneSwitch.FadeStatus(fadeStatus);
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
//void Scene::Delete() {
//	ContentDelete();
//	UpdateViewFlag(FALSE);
//	loadFlag = 0;
//}

//削除
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