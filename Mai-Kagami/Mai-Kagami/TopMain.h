#ifndef __TOPMAIN_H_INCLUDED__
#define __TOPMAIN_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"
#include "Nfc.h"
#include "Font.h"
#include "Top.h"
#include "Scene.h"

//トップ画面関係
class Top : public Scene {
public:
	Top(Font *font);
	~Top();
private:
	Font *f;
	TopLogo *topLogo; //トップロゴ
	TopTouchMessage *topTouchMessage; //NFCタッチメッセージ
	TopTouchButton *topTouchButton; //NFCタッチボタン
	Nfc nfc; //NFC監視
	int ContentUpdate(); //計算
	void ContentView(); //表示
	void ContentLoad();
	void ContentDelete();
};

#endif