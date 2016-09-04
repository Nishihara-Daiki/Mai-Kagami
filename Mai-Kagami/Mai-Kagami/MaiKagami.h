#ifndef __MAIKAGAMI_H_INCLUDED__
#define __MAIKAGAMI_H_INCLUDED__

#include "TopMain.h"
#include "SongSelectMain.h"
#include "Songs.h"
#include "ThroughMain.h"
#include "ThroughResultMain.h"
#include "PartMain.h"
#include "PartResultMain.h"
#include "Touch.h"
#include "User.h"
#include "DxLib.h"

class MaiKagami
{
public:
	MaiKagami(); //コンストラクタ
	void Update(); //計算
	void View(); //表示
	~MaiKagami(); //デストラクタ
private:
	MainScene scene; //シーン
	Font *font; //フォント
	Top *top; //トップ画面
	SongSelect *songSelect; //曲選択画面
	ThroughMain *throughMain; //通し練習プレイ画面
	ThroughResultMain *throughResultMain; //通し練習結果画面
	PartMain *partMain; //部分練習プレイ画面
	PartResultMain *partResultMain; //部分練習結果画面
	Songs *songs; //曲一覧
	Touch *touch;
	User *user; //ユーザー情報
};

#endif