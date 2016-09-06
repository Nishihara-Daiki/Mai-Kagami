#ifndef __ANIMATION_H_INCLUDED__
#define __ANIMATION_H_INCLUDED__

#define _USE_MATH_DEFINES  // 円周率M_PIを使うため
#include <math.h>
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

class Animation {
public:
	MyTime GetTime();
	void SetAnimationTime(MyTime duration, MyTime delay = 0);
//	virtual void Update() = 0;
protected:
	double UpdateRate(Easing);
	void Reset();
private:
	MyTime t = 0;		// アニメーションの現在時刻
	MyTime duration;	// アニメーション動作時間
	MyTime delay;
//	int ease = LINER;	// アニメーション種類
	void SetTime(MyTime);
};


#endif