#ifndef __PARTRESULTMAIN_H_INCLUDED__
#define __PARTRESULTMAIN_H_INCLUDED__

#include "DxLib.h"
#include "Scene.h"
#include "Font.h"
#include "Touch.h"
#include "Songs.h"
#include "PartResultDefine.h"
#include "PartResult.h"

class PartResultMain : public MainScene {
public:
	PartResultMain(Font *font, Touch *touch, Songs *songs);
	MainSceneNum Switch(const MainSceneNum scene);
	~PartResultMain();
private:
	void ContentLoad();
	void ContentUpdate();
	void ContentView();
	void ContentDelete();
	int scene;
	PartResult *partResult;
	PartFinish *partFinish;
};

#endif