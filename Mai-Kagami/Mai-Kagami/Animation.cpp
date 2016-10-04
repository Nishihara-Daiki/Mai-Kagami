#include "Animation.h"

AnimationParam::AnimationParam(double value, MyTime duration, MyTime delay, Easing ease)
	: value(value), duration(duration), delay(delay), ease(ease) {}


// アニメーションの進行割合を更新して戻り値へ
double Animation::UpdateRate(Easing ease) {
	double r, rate;
	if (t < delay)
		r = 0;
	else if (duration)
		r = (double)(t - delay) / duration;
	else
		r = 1;

	switch (ease) {
	case EaseInOut_SINE:
		rate = (1 - cos(r * DX_PI)) / 2;
		break;
	case EaseOut_SINE:
		rate = sin(r * DX_PI / 2);
		break;
	case EaseIn_SINE:
		rate = 1 - cos(r * DX_PI / 2);
		break;
	case EaseInOut_QUAD:
		rate = r < 0.5 ? r * r * 2 : - (r - 1) * (r - 1) * 2 + 1;
		break;
	case LinerInEaseOut_QUAD:
		rate = r < 0.5 ? r * 4 / 3 : - (r - 1) * (r - 1) * 4 / 3 + 1;
		break;
	case EaseInLinerOut_QUAD:
		rate = r < 0.5 ? r * r * 4 / 3 : (r * 4 - 1) / 3;
		break;
	case EaseOutBack_QUAD:
		//rate = - (r - 2.0 / 3) * (r - 2.0 / 3) * 3 + 4.0 / 3;
		rate = - (r - 3.0 / 4) * (r - 3.0 / 4) * 2 + 9.0 / 8;
		break;
	case LINER: default:
		rate = r;
		break;
	}
	if (t < duration + delay)
		t++;
	else
		t = 0;
	return rate;
}

MyTime Animation::GetTime() {
	return t;
}


// アニメーション中断 (最終値にジャンプするかどうか, キューを全てクリアするかどうか)
// TRUE,  TRUE	: Queue.back の最終値へジャンプし、キューを全てクリア
// TRUE,  FALSE	: Queue.front の最終値へジャンプし、Queue.pop() する
// FALSE, TRUE	: ジャンプせず、キューを全てクリア
// FALSE, FALSE	: ジャンプせず、Queue.pop() する (初期値)
void Animation::Stop(boolean jumpFlag, boolean deleteFlag) {
	t = 0;
	if (jumpFlag)
		JumpToTarget(deleteFlag);
	//ClearQueue(deleteFlag);
	while (!queue.empty()) {
		queue.pop();
		if (!deleteFlag)
			break;
	}
}

double Animation::UpdateValue(double nowvalue) {
	if (queue.empty())
		return nowvalue;

	AnimationParam param = queue.front();
	if (GetTime() == 0) {
		default_value = nowvalue;
		duration = param.duration;
		delay = param.delay;
	}

	double r = UpdateRate(param.ease);
	if (GetTime() == 0) {
		queue.pop();
	}
	return default_value + (param.value - default_value) * r;
}

void Animation::Add(AnimationParam param) {
	queue.push(param);
}

void Animation::Add(double value, MyTime duration, MyTime delay, Easing ease) {
	AnimationParam param(value, duration, delay, ease);
	Add(param);
}


void PosXAnimation::UpdatePosXAnimation() {
	float value = UpdateValue(GetX());
	SetX(value);
}

void PosXAnimation::JumpToTarget(boolean isQueueBack) {
	if (queue.empty()) return;
	float value = isQueueBack ? queue.back().value : queue.front().value;
	SetX(value);
}


void PosYAnimation::UpdatePosYAnimation() {
	float value = UpdateValue(GetY());
	SetY(value);
}

void PosYAnimation::JumpToTarget(boolean isQueueBack) {
	if (queue.empty()) return;
	float value = isQueueBack ? queue.back().value : queue.front().value;
	SetY(value);
}


void AlphaAnimation::UpdateAlphaAnimation() {
	int value = (int)UpdateValue((double)GetAlpha());
	SetAlpha(value);
}

void AlphaAnimation::JumpToTarget(boolean isQueueBack) {
	if (queue.empty()) return;
	int value = (int)(isQueueBack ? queue.back().value : queue.front().value);
	SetAlpha(value);
}


void ExAnimation::UpdateExAnimation() {
	double value = UpdateValue(GetEx());
	SetEx(value);
}

void ExAnimation::JumpToTarget(boolean isQueueBack) {
	if (queue.empty()) return;
	double value = isQueueBack ? queue.back().value : queue.front().value;
	SetEx(value);
}