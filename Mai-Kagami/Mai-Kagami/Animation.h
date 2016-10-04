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
	double value;	// x, y, alpha, ex, ...
	MyTime duration;
	MyTime delay;
	Easing ease;
	AnimationParam(double value, MyTime duration, MyTime delay = 0, Easing ease = LINER);
};

/*
struct PosAnimationParam : public AnimationParam {
	float x;
	float y;
	PosAnimationParam(float x, float y, MyTime duration, MyTime delay, Easing ease);
};

struct AlphaAnimationParam : public AnimationParam {
	double alpha;
	AlphaAnimationParam(double alpha, MyTime duration, MyTime delay, Easing ease);
};

struct ExAnimationParam : public AnimationParam {
	double ex;
	ExAnimationParam(double ex, MyTime duration, MyTime delay, Easing ease);
};
*/


class Animation {
public:
	void Stop(boolean jumpFlag = FALSE, boolean deleteFlag = FALSE);
	void AddAnimation(AnimationParam param);
	void AddAnimation(double value, MyTime duration, MyTime delay = 0, Easing ease = LINER);
protected:
	double UpdateRate(Easing);
	double UpdateValue(double);
	MyTime duration = 0;	// アニメーション動作時間
	MyTime delay = 0;
	MyTime GetTime();
	std::queue<AnimationParam> queue;
	double default_value;
private:
	virtual void JumpToTarget(boolean isQueueBack) = 0;	// 最終値へジャンプ(Queue.Back()の最後なのかどうか)
	//virtual void ClearQueue(boolean isAllClear) = 0;	// キューの要素全クリア
	//virtual void PopQueue() = 0;	// Queue.pop()
	MyTime t = 0;		// アニメーションの現在時刻
};


class PosXAnimation : public Animation {
public:
	void UpdatePosXAnimation();
	//void AddPosXAnimation(AnimationParam param);
	//void AddPosXAnimation(float x, float y, MyTime duration, MyTime delay = 0, Easing ease = LINER);
	virtual void SetX(const float x) = 0;
	virtual float GetX() = 0;
	//virtual float GetY() = 0;
private:
	void JumpToTarget(boolean isQueueBack);
	//void ClearQueue(boolean isAllClear);
	//void PopQueue();
	//float default_x;// , default_y;	// アニメーション開始時の座標
};



#endif