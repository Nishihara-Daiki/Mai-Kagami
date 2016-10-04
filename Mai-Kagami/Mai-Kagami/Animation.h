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

struct AnimationParam {
	double value;	// x, y, alpha, ex, ...
	MyTime duration;
	MyTime delay;
	Easing ease;
	AnimationParam(double value, MyTime duration, MyTime delay = 0, Easing ease = LINER);
};


class Animation {
public:
	void Stop(boolean jumpFlag = FALSE, boolean deleteFlag = FALSE);
	void Add(AnimationParam param);
	void Add(double value, MyTime duration, MyTime delay = 0, Easing ease = LINER);
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
	MyTime t = 0;		// アニメーションの現在時刻
};


class PosXAnimation : public Animation {
public:
	void UpdatePosXAnimation();
	virtual void SetX(const float x) = 0;
	virtual float GetX() = 0;
private:
	void JumpToTarget(boolean isQueueBack);
};



class PosYAnimation : public Animation {
public:
	void UpdatePosYAnimation();
	virtual void SetY(const float y) = 0;
	virtual float GetY() = 0;
private:
	void JumpToTarget(boolean isQueueBack);
};


class AlphaAnimation : public Animation {
public:
	void UpdateAlphaAnimation();
	virtual void SetAlpha(const int alpha) = 0;
	virtual int GetAlpha() = 0;
private:
	void JumpToTarget(boolean isQueueBack);
};


class ExAnimation : public Animation {
public:
	void UpdateExAnimation();
	virtual void SetEx(const double ex) = 0;
	virtual double GetEx() = 0;
private:
	void JumpToTarget(boolean isQueueBack);
};



#endif