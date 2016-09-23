#ifndef __THROUGHMAIN_H_INCLUDED__
#define __THROUGHMAIN_H_INCLUDED__

#include "DxLib.h"
#include "Font.h"
#include "Songs.h"
#include "Main.h"
#include "DrawText.h"
#include "ThroughStart.h"
#include "ThroughDefine.h"
#include "ThroughPlay.h"
#include "ThroughPause.h"
#include "Touch.h"
#include "KinectDistance.h"
#include "Scene.h"

class ThroughMain : public MainScene{
public:
	ThroughMain(Font *font, Touch *touch, Songs *songs);
	MainSceneNum Switch(const MainSceneNum scene);
	~ThroughMain();
private:
	void ContentLoad();
	void ContentUpdate();
	void ContentView();
	void ContentDelete();
	ThroughStart *throughStart;
	ThroughPlay *throughPlay;
	ThroughPause *throughPause;
	int scene;
};

#endif