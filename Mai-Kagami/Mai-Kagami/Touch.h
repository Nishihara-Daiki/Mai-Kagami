#ifndef __TOUCH_H_INCLUDED__
#define __TOUCH_H_INCLUDED__

#include "DxLib.h"

class Touch {
public:
	void Check(); //確認
	int Get(int num); //取得
	boolean Input(int num); // 長押しなし
	boolean Hold(int num, int wait = 30, int duration = 10);  // キーが入力されているか
	boolean Hold2(int num, int wait1 = 30, int duration1 = 10, int wait2 = 100, int duration2 = 6);  // キーが入力されているか
private:
	int key[5];
};


#endif