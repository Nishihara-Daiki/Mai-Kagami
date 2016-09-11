#include "TopMain.h"

//トップ画面コンストラクタ
Top::Top(Font *font, User *user) {
	this->user = user;
	f = font;
	topLogo = new TopLogo(HEIGHT / 3); //ロゴ初期化
	topTouchMessage = new TopTouchMessage(f, HEIGHT * 0.42); //NFCタッチメッセージ初期化
	topTouchButton = new TopTouchButton(f); //NFCタッチボタン初期化
}

//トップ画面初期化
void Top::ContentLoad() {
	StopMusic();
	topLogo->Load();
	topTouchMessage->Init();
	nfc.Init();
}

//場面の切り替え
MainScene Top::Switch(const MainScene scene) {
	char* id = nfc.GetId();
	if (id[0] != '\0') {
		user->SetUserId(id);
		//printfDx("id:%s", id);
		nfc.reset_calledCont();
		SetDeleteFlag(TRUE);  // 削除フラグセット
		return SONG_SELECT;
	}
	return TOP;
}

//トップ画面計算
void Top::ContentUpdate() {
	if (nowScene == TOP) {
		Load();
		topTouchMessage->Update(); //NFCタッチメッセージ計算
	}
	else {
		UpdateViewFlag(FALSE, SCENE_DELAY);
		Delete();
		//UpdateViewFlag(FALSE);
	}
}

//トップ画面表示
void Top::ContentView() {
	topLogo->View(sceneOpacity); //ロゴ表示
	topTouchMessage->View(sceneOpacity); //NFCタッチメッセージ表示
	topTouchButton->View(sceneOpacity); //NFCタッチボタン表示
}

void Top::ContentDelete() {
	topLogo->Release();
}

Top::~Top() {
	delete topLogo;
	delete topTouchButton;
	delete topTouchMessage;
}