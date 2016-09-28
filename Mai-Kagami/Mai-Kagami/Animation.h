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
//	MyTime t = 0;		// �A�j���[�V�����̌��ݎ���
//	MyTime duration;	// �A�j���[�V�������쎞��
//	MyTime delay;
////	int ease = LINER;	// �A�j���[�V�������
//	void SetTime(MyTime);
//};




struct AnimationParam {
	MyTime duration;
	MyTime delay;
	Easing ease;
	AnimationParam(MyTime duration, MyTime delay = 0, Easing ease = LINER);
};

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



class Animation {
public:
	void Stop(boolean jumpFlag = FALSE, boolean deleteFlag = FALSE);
protected:
	double UpdateRate(Easing);
	MyTime duration = 0;	// �A�j���[�V�������쎞��
	MyTime delay = 0;
	MyTime GetTime();
private:
	virtual void JumpToTarget(boolean isQueueBack) = 0;	// �ŏI�l�փW�����v(Queue.Back()�̍Ō�Ȃ̂��ǂ���)
	virtual void ClearQueue(boolean isAllClear) = 0;	// �L���[�̗v�f�S�N���A
	//virtual void PopQueue() = 0;	// Queue.pop()
	MyTime t = 0;		// �A�j���[�V�����̌��ݎ���
};


class PosAnimation : public Animation {
public:
	void UpdatePosAnimation();
	void AddPosAnimation(PosAnimationParam param);
	void AddPosAnimation(float x, float y, MyTime duration, MyTime delay = 0, Easing ease = LINER);
	virtual void SetPos(const float x, const float y) = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
private:
	void JumpToTarget(boolean isQueueBack);
	void ClearQueue(boolean isAllClear);
	//void PopQueue();
	float default_x, default_y;	// �A�j���[�V�����J�n���̍��W
	std::queue<PosAnimationParam> queue;
};

#endif