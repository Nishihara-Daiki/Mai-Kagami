#ifndef __ANIMATION_H_INCLUDED__
#define __ANIMATION_H_INCLUDED__

//#define _USE_MATH_DEFINES  // 円周率M_PIを使うため
#include <math.h>
#include <queue>
#include "DxLib.h"

typedef unsigned long MyTime;

typedef enum {
	LINER,			// 線形
	EaseInOut_SINE,	// 正弦波(遅早遅)
	EaseOut_SINE,	// 正弦波(早遅)
	EaseIn_SINE,	// 正弦波(遅早)
	EaseInOut_QUAD,	// 2次式
	LinerInEaseOut_QUAD,	// 1次=>2次
	EaseInLinerOut_QUAD,	// 2次=>1次
	EaseOutBack_QUAD, // 二次式(ちょっとはみ出て戻る)
} Easing;
//
//class Animation {
//public:
//	MyTime GetTime();
//	void SetAnimationTime(MyTime duration, MyTime delay = 0);
////	virtual void Update() = 0;
//protected:
//	double UpdateRate(Easing);
//	void Reset();
//private:
//	MyTime t = 0;		// アニメーションの現在時刻
//	MyTime duration;	// アニメーション動作時間
//	MyTime delay;
////	int ease = LINER;	// アニメーション種類
//	void SetTime(MyTime);
//};




struct AnimationParam {
public:
	MyTime duration;
	MyTime delay;
	Easing ease;
};

struct PosAnimationParam : public AnimationParam {
	float x;
	float y;
};

struct AlphaAnimationParam : public AnimationParam {
	float alpha;
};

struct ExAnimationParam : public AnimationParam {
	float ex;
};



class Animation {
public:
	void Stop(boolean jumpFlag = FALSE, boolean deleteFlag = FALSE);
protected:
	double UpdateRate(Easing);
	MyTime duration = 0;	// アニメーション動作時間
	MyTime delay = 0;
	MyTime GetTime();
private:
	virtual void JumpToTarget() = 0;	// 最終値へジャンプし、Queue.pop()
	virtual void ClearQueue() = 0;	// キューの要素全クリア
	MyTime t = 0;		// アニメーションの現在時刻
};


class PosAnimation : public Animation {
public:
	void UpdatePosAnimation();
	void AddPosAnimation(PosAnimationParam param);
	virtual void SetPos(const float x, const float y) = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
private:
	void JumpToTarget();
	void ClearQueue();
	float default_x, default_y;	// アニメーション開始時の座標
	std::queue<PosAnimationParam> queue;
};

#endif