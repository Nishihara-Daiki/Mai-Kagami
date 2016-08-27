#include "Touch.h"

//Šm”F
void Touch::Check() {
	int k = KEY_INPUT_1;
	for (int i = 0; i < 5; i++) {
		if (CheckHitKey(k++))
			key[i]++;
		else
			key[i] = 0;
	}
}

//Žæ“¾
int Touch::Get(int num) {
	return key[num];
}

boolean Touch::Input(int num, int wait, int duration) {
	int key = Get(num);
	return key == 1 || wait <= key && !((key - wait) % duration);
}

boolean Touch::Input2(int num, int wait1, int duration1, int wait2, int duration2) {
	int key = Get(num);
	return key == 1
		|| wait1 <= key && key < wait2 && !((key - wait1) % duration1)
		|| wait2 + (wait2 - wait1) % duration1 <= key && !((key - wait2 - (wait2 - wait1) % duration1) % duration2);
}
