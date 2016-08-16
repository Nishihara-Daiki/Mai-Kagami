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
#include "ThroughResult.h"
#include "ThroughDetail.h"
#include "Touch.h"
#include "KinectDistance.h"
#include "Scene.h"

class ThroughMain : public Scene{
public:
	ThroughMain(Font *font, Touch *touch, Songs *songs);
	void ContentUpdate();
	MainScene Switch(const MainScene scene);
	void ContentView();
	~ThroughMain();
private:
	ThroughStart *throughStart;
	ThroughPlay *throughPlay;
	ThroughPause *throughPause;
	ThroughResult *throughResult;
	ThroughDetail *throughDetail;
	void ContentLoad();
	void ContentDelete();
	ThroughScene scene;
};

#endif