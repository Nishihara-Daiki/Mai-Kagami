#ifndef __ANIMATION_H_INCLUDED__
#define __ANIMATION_H_INCLUDED__

#define _USE_MATH_DEFINES  // �~����M_PI���g������
#include <math.h>
#include "DxLib.h"

typedef unsigned long MyTime;

typedef enum {
	LINER,			// ���`
	EaseInOut_SINE,	// �����g(�x���x)
	EaseOut_SINE,	// �����g(���x)
	EaseIn_SINE,	// �����g(�x��)
	EaseInOut_QUAD,	// 2����
	LinerInEaseOut_QUAD,	// 1��=>2��
	EaseInLinerOut_QUAD,	// 2��=>1��
	EaseOutBack_QUAD, // �񎟎�(������Ƃ͂ݏo�Ė߂�)
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
	MyTime t = 0;		// �A�j���[�V�����̌��ݎ���
	MyTime duration;	// �A�j���[�V�������쎞��
	MyTime delay;
//	int ease = LINER;	// �A�j���[�V�������
	void SetTime(MyTime);
};


#endif