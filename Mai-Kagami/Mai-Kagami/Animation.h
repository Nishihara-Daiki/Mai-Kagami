#ifndef __ANIMATION_H_INCLUDED__
#define __ANIMATION_H_INCLUDED__

//#define _USE_MATH_DEFINES  // �~����M_PI���g������
#include <math.h>
#include <queue>
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
	MyTime duration = 0;	// �A�j���[�V�������쎞��
	MyTime delay = 0;
	MyTime GetTime();
	std::queue<AnimationParam> queue;
	double default_value;
private:
	virtual void JumpToTarget(boolean isQueueBack) = 0;	// �ŏI�l�փW�����v(Queue.Back()�̍Ō�Ȃ̂��ǂ���)
	MyTime t = 0;		// �A�j���[�V�����̌��ݎ���
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