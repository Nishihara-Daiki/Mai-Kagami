#include "PartOptionPop.h"

PartOptionSpeedPop::PartOptionSpeedPop(Font *font, Songs *songs, Touch *touch, const int mainScene, const int speedScene)
	: SpeedPop(font, songs, touch) {
	this->mainScene = mainScene;
	this->speedScene = speedScene;
}

int PartOptionSpeedPop::Switch(const int scene) {
	if (button->GetTouch() == 1) {
		song->danceMovie->SetSpeed();
		return mainScene;
	}
	return scene;
}

void PartOptionSpeedPop::ContentUpdate() {
	static int lastScene = mainScene;
	if (nowScene == speedScene) {
		if (lastScene == nowScene)
			SpeedPop::ContentUpdate();
		viewFlag = TRUE;
	}
	else {
		viewFlag = FALSE;
	}
	lastScene = nowScene;
}

PartOptionPartPop::PartOptionPartPop(Font *font, Songs *songs, Touch *touch, const int mainScene, const int partScene)
	: PartPop(font, songs, touch) {
	this->mainScene = mainScene;
	this->partScene = partScene;
}

int PartOptionPartPop::Switch(const int scene) {
	if (button->GetTouch() == 1) {
		song->danceMovie->SetPart();
		return mainScene;
	}
	return scene;
}

void PartOptionPartPop::ContentUpdate() {
	static int lastScene = mainScene;
	if (nowScene == partScene) {
		if (lastScene == mainScene)
			PartPop::Init();
		else if (lastScene == nowScene)
			PartPop::ContentUpdate();
		viewFlag = TRUE;
	}
	else {
		viewFlag = FALSE;
	}
	lastScene = nowScene;
}

PartOptionPreview::PartOptionPreview(Font *font, Songs *songs, Touch *touch, const int mainScene, const int partScene, const int speedScene) {
	this->songs = songs;
	this->mainScene = mainScene;
	this->partScene = partScene;
	this->speedScene = speedScene;
	button[0] = new CircleButton(font, touch, "区間", 0, WIDTH * 0.8);
	button[1] = new CircleButton(font, touch, "", 2, WIDTH * 0.8);
	message = new MyDrawText(font, "変更したいものを選んでください", WIDTH * 0.75, HEIGHT * 0.45, 1, 30);
	caption[0] = new MyDrawText(font, "開始：", WIDTH * 0.8, HEIGHT * 0.53, 2, 30);
	caption[1] = new MyDrawText(font, "終了：", WIDTH * 0.8, HEIGHT * 0.555, 2, 30);
	caption[2] = new MyDrawText(font, "速度：", WIDTH * 0.8, HEIGHT * 0.6, 2, 30);
	para[0] = new MyDrawText(font, "", WIDTH * 0.81, HEIGHT * 0.53, 0, 30, "Yellow");
	para[1] = new MyDrawText(font, "", WIDTH * 0.81, HEIGHT * 0.555, 0, 30, "Yellow");
	para[2] = new MyDrawText(font, "", WIDTH * 0.81, HEIGHT * 0.6, 0, 30, "Yellow");
}

int PartOptionPreview::Switch(const int scene) {
	if (button[0]->GetTouch() == 1)
		return partScene;
	if (button[1]->GetTouch() == 1)
		return speedScene;
	return scene;
}
void PartOptionPreview::ContentUpdate() {
	Song *song = songs->GetSong(songs->GetNowSong());
	if (nowScene == mainScene) {
		char str[256];
		sprintf_s(str, sizeof(str), "×%1.1lf", song->danceMovie->GetSpeed());
		para[0]->ChangeText(song->GetPart(song->StartPart())->GetName());
		para[1]->ChangeText(song->GetPart(song->EndPart())->GetName());
		para[2]->ChangeText(str);
		viewFlag = TRUE;
	}
	else {
		viewFlag = FALSE;
	}
}

void PartOptionPreview::ContentView() {
	for (int i = 0; i < 2; i++)
		button[i]->View();
	message->View();
	for (int i = 0; i < 3; i++) {
		caption[i]->View();
		para[i]->View();
	}
}

PartOptionPreview::~PartOptionPreview() {
	for (int i = 0; i < 2; i++)
		delete button[i];
	delete message;
	for (int i = 0; i < 3; i++) {
		delete caption[i];
		delete para[i];
	}
}

PartOptionPop::PartOptionPop(Font *font, Songs *songs, Touch *touch, const int mainScene, const int partScene, const int speedScene, PartOptionPreview *partOptionPreview) {
	this->songs = songs;
	this->mainScene = mainScene;
	this->partScene = partScene;
	this->speedScene = speedScene;
	this->partOptionPreview = partOptionPreview;
	speedPop = new PartOptionSpeedPop(font, songs, touch, mainScene, speedScene);
	partPop = new PartOptionPartPop(font, songs, touch, mainScene, partScene);
}

int PartOptionPop::Switch(const int scene) {
	if (scene == mainScene)
		return partOptionPreview->Switch(scene);
	if (scene == partScene)
		return partPop->Switch(scene);
	if(scene == speedScene)
		return speedPop->Switch(scene);
	return scene;
}

void PartOptionPop::Load() {
	speedPop->Load();
	partPop->Load();
	partOptionPreview->Load();
}

void PartOptionPop::Delete() {
	speedPop->Delete();
	partPop->Delete();
	partOptionPreview->Delete();
}

void PartOptionPop::ContentUpdate() {
	speedPop->Update(nowScene);
	partPop->Update(nowScene);
	partOptionPreview->Update(nowScene);
	Song *song = songs->GetSong(songs->GetNowSong());

	if (nowScene == mainScene || nowScene == partScene || nowScene == speedScene) {
		viewFlag = TRUE;
		if (nowScene == mainScene) {
			song->ChangeStart(0);
			song->ChangeEnd(0);
		}
	}
	else {
		viewFlag = FALSE;
	}
}

void PartOptionPop::ContentView() {
	speedPop->View();
	partPop->View();
	partOptionPreview->View();
}

PartOptionPop::~PartOptionPop

() {
	delete speedPop;
	delete partPop;
	delete partOptionPreview;
}