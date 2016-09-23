#include "ThroughDetail.h"

ThroughFinish::ThroughFinish(Font *font, Touch *touch) {
	blackBox = new BlackBox();
	button[0] = new CircleButton(font, touch, "�������ߗ��K", 0, WIDTH * 0.75, "White");
	button[1] = new CircleButton(font, touch, "������x", 1, WIDTH * 0.75, "White");
	button[2] = new CircleButton(font, touch, "�������K", 2, WIDTH * 0.75, "White");
	button[3] = new CircleButton(font, touch, "�ȑI�����", 3, WIDTH * 0.75, "White");
}

ThroughResultScene ThroughFinish::Switch(const ThroughResultScene scene) {
	if (button[0]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_PART_OPTION;
	if (button[1]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_PLAY;
	if (button[2]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_PART_OPTION;
	if (button[3]->GetTouch() == 1)
		return THROUGH_RESULT_BACK_SONG_SELECT;
	return scene;
}

void ThroughFinish::ContentUpdate() {
	if (nowScene == THROUGH_RESULT_FINISH)
		UpdateViewFlag(TRUE, SCENE_IN_WAIT);
	else
		UpdateViewFlag(FALSE);
}

void ThroughFinish::ContentView() {
	blackBox->View();
	for (int i = 0; i < 4; i++)
		button[i]->View();
}

ThroughFinish::~ThroughFinish() {
	delete blackBox;
	for (int i = 0; i < 4; i++)
		delete button[i];
}

ThroughDetailScreen::ThroughDetailScreen(Font *font, Songs *songs, Touch *touch) {
	this->songs = songs;
	title = new DrawTitle(font, "�̓_����");
	timingBar = new TimingBar(font);
	expressionBar = new ExpressionBar(font);
	resultComment = new ResultComment(font);
	resultBody = new ResultBody(font);
	resultGraph = new ResultGraph(font);
	button = new CircleButton2(font, touch, "����", 4);
}

ThroughResultScene ThroughDetailScreen::Switch(const ThroughResultScene scene) {
	if (button->GetTouch() == 1)
		return THROUGH_RESULT_FINISH;
	return scene;
}

void ThroughDetailScreen::Load() {
	Song *song = songs->GetSong(songs->GetNowSong());
	char *comment = "B��������T�r�ɓ����Ă���T�r�̏I���ɂ����Ă����\n�̂悤�Ɏv���܂��B�������d�_�I�ɗ��K���܂��傤�B";
	int point[] = { 1, 1, 2, 3 };
	int max = 10;
	int score[] = { 50, 80, 40, 90, 100, 70, 60, 80, 40, 90 };
	timingBar->Load(4);
	expressionBar->Load(2);
	resultBody->Load(point);
	resultComment->Load(comment);
	resultGraph->Load(score, max, song);
}

void ThroughDetailScreen::ContentUpdate() {
	if (nowScene == THROUGH_RESULT_DETAIL || nowScene == THROUGH_RESULT_FINISH)
		UpdateViewFlag(TRUE, SCENE_IN_WAIT);
	else
		UpdateViewFlag(FALSE);
}

void ThroughDetailScreen::ContentView() {
	title->View();
	timingBar->View();
	expressionBar->View();
	resultComment->View();
	button->View();
	resultBody->View();
	resultGraph->View();
}

void ThroughDetailScreen::Delete() {
	resultGraph->Delete();
	resultBody->Delete();
}

ThroughDetailScreen::~ThroughDetailScreen() {
	delete title;
	delete timingBar;
	delete expressionBar;
	delete resultComment;
	delete button;
	delete resultGraph;
}

ThroughDetail::ThroughDetail(Font *font, Songs *songs, Touch *touch) {
	throughDetailScreen = new ThroughDetailScreen(font, songs, touch);
	throughFinish = new ThroughFinish(font, touch);
}

ThroughResultScene ThroughDetail::Switch(const ThroughResultScene scene) {
	switch (scene)
	{
	case THROUGH_RESULT_DETAIL:
		return throughDetailScreen->Switch(scene);
	case THROUGH_RESULT_FINISH:
		return throughFinish->Switch(scene);
	}
	return scene;
}

void ThroughDetail::Load() {
	throughDetailScreen->Load();
	throughFinish->Load();
}

void ThroughDetail::ContentUpdate() {
	throughFinish->Update(nowScene);
	throughDetailScreen->Update(nowScene);
	if (nowScene == THROUGH_RESULT_DETAIL || nowScene == THROUGH_RESULT_FINISH)
		UpdateViewFlag(TRUE, SCENE_IN_WAIT);
	else
		UpdateViewFlag(FALSE);
}

void ThroughDetail::ContentView() {
	throughDetailScreen->View();
	throughFinish->View();
}

void ThroughDetail::Delete() {
	throughDetailScreen->Delete();
}

ThroughDetail::~ThroughDetail() {
	delete throughDetailScreen;
	delete throughFinish;
}