#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DURATION 120  // 画面切り替えにかかる時間

enum {
	NOT_FADE,	// 場面切り替え中ではない
	FADING_IN,	// フェードイン中
	FADING_OUT,	// フェードアウト中
	FADE_WAIT,	// フェードイン・アウト開始までの待ち
};

//サブ場面定義
class SubScene {
public:
	void Update(const int scene); //更新
	void View(); //表示
	void Load(); //ロード
	void Delete(); //削除
	boolean CheckView(); //表示中かどうか確認する(TRUE:表示中、FALSE：非表示中)
protected:
	int nowScene;
	long fadeCount = 0;	// 場面切り替え時のフェードイン・アウトのカウンタ
	virtual void ContentView() = 0; //表示詳細
	virtual void ContentUpdate() = 0; //更新詳細
	void UpdateViewFlag(boolean flag, long duration = SCENE_DURATION, long wait = 60);
private:
	boolean viewFlag = FALSE;		//表示用フラグ(TRUE:表示、FALSE：非表示)
	short fadeStatus = NOT_FADE;	// 場面切り替えの状態
	double sceneOpacity = 1.0;
};

//場面定義
class MainScene : public SubScene {
protected:
	void Load(); //ロード
	void Delete(); //削除
	void SetDeleteFlag(boolean status);
private:
	virtual void ContentLoad() = 0; //ロード詳細
	virtual void ContentDelete() = 0; //削除詳細
	int loadFlag = 0; //ロード確認用（0：未ロード、1：ロード中、2：ロード完了）
	boolean deleteFlag = FALSE;	// 削除確認用 (FALSE:未削除(通常) / TRUE:削除中)
};

typedef struct {
public:
	void SetOpacity(const double opacity) { this->opacity = opacity; };
	double GetDrawOpacity() { return opacity; };
private:
	double opacity = 1.0;
} SceneSwitch;

extern SceneSwitch gSceneSwitch;

#endif