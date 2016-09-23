#ifndef __PARTMAIN_H_INCLUDED__
#define __PARTMAIN_H_INCLUDED__

#include "DxLib.h"
#include "Scene.h"
#include "Main.h"
#include "Font.h"
#include "Songs.h"
#include "Touch.h"
#include "PartDefine.h"
#include "PartPlay.h"
#include "PartPause.h"

class PartMain : public MainScene {
public:
	PartMain(Font *font, Touch *touch, Songs *songs);
	MainSceneNum Switch(const MainSceneNum scene);
	~PartMain();
private:
	void ContentLoad();
	void ContentUpdate();
	void ContentView();
	void ContentDelete();
	PartStart *partStart;
	PartPlay *partPlay;
	PartPause *partPause;
	int scene;
};

#endif