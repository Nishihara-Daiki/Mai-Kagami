#include "Animation.h"

AnimationParam::AnimationParam(double value, MyTime duration, MyTime delay, Easing ease)
	: value(value), duration(duration), delay(delay), ease(ease) {}
//
//PosAnimationParam::PosAnimationParam(float x, float y, MyTime duration, MyTime delay, Easing ease)
//	: x(x), y(y), AnimationParam(duration, delay, ease) {}
//
//AlphaAnimationParam::AlphaAnimationParam(double alpha, MyTime duration, MyTime delay, Easing ease)
//	: alpha(alpha), AnimationParam(duration, delay, ease) {}
//
//ExAnimationParam::ExAnimationParam(double ex, MyTime duration, MyTime delay, Easing ease)
//	: ex(ex), AnimationParam(duration, delay, ease) {}


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

//// パラメータ代入
////void Animation::SetRate(MyTime _duration, int _ease = LINER) {
//void Animation::SetAnimationTime(MyTime duration, MyTime delay) {
//	this->duration = duration <= 0 ? 0 : duration;
//	this->delay = delay <= 0 ? 0 : delay;
////	ease = _ease;
//}

//// アニメーション時刻を強制変更 (引数に0を入れれば時刻初期化)
//void Animation::SetTime(MyTime _t) {
//	t = _t;
//}

MyTime Animation::GetTime() {
	return t;
}
//
//void Animation::Reset() {
//	SetTime(0);
//}

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
		//default_y = GetY();
		duration = param.duration;
		delay = param.delay;
	}

	double r = UpdateRate(param.ease);
	if (GetTime() == 0) {
		queue.pop();
	}
	return default_value + (param.value - default_value) * r;
}

void Animation::AddAnimation(AnimationParam param) {
	queue.push(param);
}

void Animation::AddAnimation(double value, MyTime duration, MyTime delay, Easing ease) {
	AnimationParam param(value, duration, delay, ease);
	AddAnimation(param);
}

void PosXAnimation::UpdatePosXAnimation() {
	//if (queue.empty())
	//	return;

	//AnimationParam param = queue.front();
	//if (GetTime() == 0) {
	//	default_value = GetX();
	//	//default_y = GetY();
	//	duration = param.duration;
	//	delay = param.delay;
	//}

	//double r = UpdateRate(param.ease);
	//if (GetTime() == 0) {
	//	queue.pop();
	//}
	//float value = default_value + (param.value - default_value) * r;
	float value = UpdateValue(GetX());
	SetX(value);
}
//
//void PosXAnimation::AddPosXAnimation(AnimationParam param) {
//	queue.push(param);
//}
//
//void PosXAnimation::AddPosXAnimation(float x, float y, MyTime duration, MyTime delay, Easing ease){
//	AnimationParam param(x, duration, delay, ease);
//	AddPosXAnimation(param);
//}

void PosXAnimation::JumpToTarget(boolean isQueueBack) {
	if (queue.empty()) return;
	float value = isQueueBack ? queue.back().value : queue.front().value;
	SetX(value);
}