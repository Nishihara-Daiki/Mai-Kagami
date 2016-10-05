#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DURATION	60	// 画面切り替えフェードアニメーション時間
#define SCENE_IN_WAIT	60	// 画面切り替えフェードインまでの待ち時間

enum {
	NOT_FADE,	// 場面切り替え中ではない
	FADING_IN,	// フェードイン中
	FADING_OUT,	// フェードアウト中
	FADE_WAIT,	// フェードイン・アウト開始までの待ち
};

enum {
	UNLOADED,	// 未ロード
	THREADING,	// 立てたスレッドの計算中
	LOADING,	// 画像ロード中
	LOADED,		// 完了
};


class ViewFlag {
public:
	boolean CheckView(); //表示中かどうか確認する(TRUE:表示中、FALSE：非表示中)
protected:
	void UpdateViewFlag(boolean flag, long wait = 0, long duration = SCENE_DURATION);
	boolean GetViewFlag();
	long GetFadeCount();
	double GetSceneOpacity();
	virtual void SetOpacity() = 0;  // グローバル変数にセット
private:
	boolean viewFlag = FALSE;		//表示用フラグ(TRUE:表示、FALSE：非表示)
	long fadeCount = 0;	// 場面切り替え時のフェードイン・アウトのカウンタ
	short fadeStatus = NOT_FADE;	// 場面切り替えの状態
	double sceneOpacity = 1.0;
};


// 場面定義
class Scene: public ViewFlag {
public:
	void Update(const int scene); //更新
	void View(); //表示
	void Load(); //ロード
	void Delete(); //削除
protected:
	int nowScene;
	virtual void ContentView() = 0; //表示詳細
	virtual void ContentUpdate() = 0; //更新詳細
};


class SubScene : public Scene {
private:
	void SetOpacity();
};


class MainScene : public Scene {
protected:
	void Load(); //ロード
	void Delete(); //削除
	void SetDeleteFlag(boolean status);
private:
	void SetOpacity();
	virtual void ContentLoad() = 0; //ロード詳細
	virtual void ContentDelete() = 0; //削除詳細
	int loadStatus = UNLOADED; //ロード確認用（0：未ロード、1：ロード中、2：ロード完了）
	boolean deleteFlag = FALSE;	// 削除確認用 (FALSE:未削除(通常) / TRUE:削除中)
};

typedef struct {
public:
	void SetSubOpacity(const double opacity) { subOpacity = opacity; };
	void SetMainOpacity(const double opacity) { mainOpacity = opacity; };
	double GetDrawOpacity() { return mainOpacity * subOpacity; };
private:
	double subOpacity = 1.0;
	double mainOpacity = 1.0;
} SceneSwitch;

extern SceneSwitch gSceneSwitch;

#endif