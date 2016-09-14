#include "StartScreen.h"

StartSceen::StartSceen(Font *f, const int startScene, const int playScene) {
	this->startScene = startScene;
	this->playScene = playScene;
	blackBox = new BlackBox(&sceneOpacity);
	myDrawGraph = new MyDrawGraph(WIDTH * 0.5, HEIGHT * 0.45, "img/start.png", &sceneOpacity);
	myDrawGraph->Load();
	wait = new MyDrawText(f, "", WIDTH * 0.5, HEIGHT * 0.3, 1, 40, &sceneOpacity);
	caution = new MyDrawText(f, "本体から2メートル以上離れてください", WIDTH * 0.5, HEIGHT * 0.67, 1, 46, &sceneOpacity, "Blue");
	annotation = new MyDrawTexts(f, "※2メートル以内に入ると\n自動的に曲が一時停止します", WIDTH * 0.5, HEIGHT * 0.75, 1, 36, 20, &sceneOpacity);
}

void StartSceen::Load() {
	wait->ChangeText("準備中…");
	annotation->SetViewFlag(TRUE);
}

void StartSceen::ContentUpdate() {
	if (nowScene == startScene) {
		UpdateViewFlag(TRUE);
	}
	else {
		UpdateViewFlag(FALSE);
		if (nowScene = playScene) {
			wait->ChangeText("一時停止中");
			annotation->SetViewFlag(FALSE);
		}
	}
}

void StartSceen::ContentView() {
	blackBox->View();
	myDrawGraph->View();
	wait->View();
	caution->View();
	annotation->View();
}

StartSceen::~StartSceen() {
	delete myDrawGraph;
	delete wait;
	delete caution;
	delete annotation;
	delete blackBox;
}