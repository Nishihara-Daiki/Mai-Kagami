#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DELAY 120  // 画面切り替えにかかる時間

enum {
	NOT_FADE,	// 場面切り替え中ではない
	FADING_IN,	// フェードイン中
	FADING_OUT,	// フェードアウト中
};

//サブ場面定義
class SubScene {
public:
	void Update(const int scene); //更新
	void View(); //表示
	void Load(); //ロード
	void Delete(); //削除
//	void SetDelay(long);
	boolean CheckView(); //表示中かどうか確認する(TRUE:表示中、FALSE：非表示中)
protected:
	int nowScene;
	long delayCount = 0;	// 場面切り替え時のディレイ
	virtual void ContentView() = 0; //表示詳細
	virtual void ContentUpdate() = 0; //更新詳細
	void UpdateViewFlag(boolean flag, long delay = SCENE_DELAY);
private:
	boolean viewFlag = FALSE;		//表示用フラグ(TRUE:表示、FALSE：非表示)
	short fadeStatus = NOT_FADE;	// 場面切り替えの状態
	double sceneOpacity = 1.0;
};

//場面定義
class Scene : public SubScene {
protected:
	void Load(); //ロード
	void Delete(); //削除
	void SetDeleteFlag(boolean status);
private:
	virtual void ContentLoad() = 0; //ロード詳細
	virtual void ContentDelete() = 0; //削除詳細
	int loadFlag = 0; //ロード確認用（0：未ロード、1：ロード中、2：ロード完了）
	int deleteFlag = FALSE;	// 削除確認用 (FALSE:未削除(通常) / TRUE:削除中)
};

typedef struct {
public:
	void SetOpacity(const double opacity) {
		//switch (fadeStatus) {
		//	case FADING_IN:  fadeInOpacity = opacity; break;
		//	case FADING_OUT: fadeOutOpacity = opacity; break;
		//	default: fadeInOpacity = fadeOutOpacity = 1.0; break;
		//}
		this->opacity = opacity;
	};
	//double GetOpacity() { return opacity; };
	double GetDrawOpacity() {
		//switch (fadeStatus) {
		//	case NOT_FADE:   return 1.0;
		//	case FADING_IN:  return fadeInOpacity;
		//	case FADING_OUT: return fadeOutOpacity;
		//}
		return opacity;
	};
	//void FadeStatus(short flag) { fadeStatus = flag; };
private:
	//double fadeInOpacity = 1.0;
	//double fadeOutOpacity = 1.0;
	double opacity = 1.0;
	//short fadeStatus;
} SceneSwitch;

extern SceneSwitch gSceneSwitch;

#endif