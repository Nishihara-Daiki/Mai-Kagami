#ifndef __TOPMAIN_H_INCLUDED__
#define __TOPMAIN_H_INCLUDED__

#include "Nfc.h"
#include "DxLib.h"
#include "Main.h"
#include "Font.h"
#include "Top.h"
#include "Scene.h"
#include "User.h"

//トップ画面関係
class Top : public MainScene {
public:
	Top(Font *font, User *user);
	MainSceneNum Switch(const MainSceneNum scene);
	~Top();
private:
	Font *f;
	TopLogo *topLogo; //トップロゴ
	TopTouchMessage *topTouchMessage; //NFCタッチメッセージ
	TopTouchButton *topTouchButton; //NFCタッチボタン
	Nfc nfc; //NFC監視
	User *user;
	void ContentUpdate(); //計算
	void ContentView(); //表示
	void ContentLoad();
	void ContentDelete();
};

#endif