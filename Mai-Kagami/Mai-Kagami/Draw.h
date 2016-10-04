#ifndef __DRAW_H_INCLUDED__
#define __DRAW_H_INCLUDED__

#include <math.h>
#include "DxLib.h"
#include "Main.h"
#include "Animation.h"

//色関係
class Color {
public:
	Color(const char *color);
	void ChangeColor(const char *color);
protected:
	int Get();
private:
	int c;
};

//表示位置用クラス
//class Pos : public Animation {
class Pos : public PosXAnimation, public PosYAnimation {
public:
	void ChangePos(const float x, const float y); //座標変更
	void SetPos(const float x, const float y);	// ChangePosの別名
	void Update();	// アニメーション更新
	void Stop(boolean jumpFlag = FALSE, boolean deleteFlag = FALSE);
	float GetX(); //x座標取得
	float GetY(); //y座標取得
	void SetX(const float x);
	void SetY(const float y);
protected:
	Pos();
	Pos(const float x, const float y); //初期化
	float x, y;
};

//描画用クラス
class Draw : public Pos, public AlphaAnimation {
public:
	Draw();
	Draw(const float x, const float y);
	void View();
	void SetAlpha(const int alpha = 255); //透明度指定
	int GetAlpha();
	void Update();	// アニメーション更新
	void Stop(boolean jumpFlag = FALSE, boolean deleteFlag = FALSE);
	void SetViewFlag(const boolean viewFlag);
	void SetExceptFadeFlag(const boolean flag);
private:
	virtual void ContentView() = 0; //表示メソッド
	int alpha = 255; //透明度
	boolean viewFlag = TRUE;
	boolean exceptFadeFlag = FALSE;	// フェードの対象から除外
};

//描画用クラス（位置指定あり）
class Draw2 : public Draw {
public:
	Draw2(const int position);
	Draw2(const float x, const float y, const int pos);
	void ChangePos();
	void ChangePos(const float x, const float y);
	float GetX(); //x座標取得
	float GetY(); //y座標取得
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;
protected:
	int p; //ポジション情報
private :
	float xx, yy; //座標
};

#endif