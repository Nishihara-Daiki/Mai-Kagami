#ifndef __ANIMATION_H_INCLUDED__
#define __ANIMATION_H_INCLUDED__

#include "Animation.h"
#define _USE_MATH_DEFINES  // 円周率M_PIを使うため
#include <math.h>
#include "DxLib.h"

typedef unsigned long MyTime;

class Animation {
public:
	MyTime GetTime();
	void Reset();
	void SetAnimationTime(MyTime duration, MyTime delay = 0);
	enum Easing {
		LINER,			// 線形
		EaseInOut_SINE,	// 正弦波(遅早遅)
		EaseOut_SINE,	// 正弦波(早遅)
		EaseIn_SINE,	// 正弦波(遅早)
		EaseInOut_QUAD,	// 2次式
		LinerInEaseOut_QUAD,	// 1次=>2次
		EaseInLinerOut_QUAD,	// 2次=>1次
		EaseOutBack_QUAD, // 二次式(ちょっとはみ出て戻る)
	};
protected:
	double UpdateRate(Easing);
	void SetTime(MyTime);
private:
	MyTime t = 0;		// アニメーションの現在時刻
	MyTime duration;	// アニメーション動作時間
	MyTime delay;
//	int ease = LINER;	// アニメーション種類
};


#endif