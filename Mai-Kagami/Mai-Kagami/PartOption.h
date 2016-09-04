#ifndef __PARTOPTION_H_INCLUDED__
#define __PARTOPTION_H_INCLUDED__

#include "DxLib.h"
#include "PartOptionPop.h"
#include "SongSelectDefine.h"

class PartOptionPreview2 : public PartOptionPreview {
public:
	PartOptionPreview2(Font *font, Songs *songs, Touch *touch);
	int Switch(const int scene);
	~PartOptionPreview2();
private:
	void ContentView();
	Button *button[2];
};

class PartOptionButton : public PartOptionPop {
public:
	PartOptionButton(Font *font, Songs *songs, Touch *touch);
};


#endif