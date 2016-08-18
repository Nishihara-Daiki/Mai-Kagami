#include "ThroughResultObject.h"

ScoreBar::ScoreBar(Font *font, const float y, const char *title, const char *para1, const char *para2)
 : Draw(WIDTH * 0.475, y) {
	const float height = 110;
	this->title = new MyDrawTextLine(font, title, GetX(), GetY(), 0, 24, WIDTH * 0.3, 2);
	mark = new MyDrawGraph(0, GetY() + height - 50, "img/mark.png");
	score = new MyDrawText(font, "", 0, GetY() + height - 55, 1, 30);
	para[0] = new MyDrawText(font, para1, GetX() - 100, GetY() + height, 2, 20);
	para[1] = new MyDrawText(font, para2, GetX() + 100, GetY() + height, 0, 20);
	for (int i = 0; i < 8; i++)
		box[i] = new MyDrawBox(GetX() - 77 + i * 22, GetY() + height, 20, 40);
}

void ScoreBar::Load(const int p) {
	char point[10];
	sprintf_s(point, sizeof(point), "%d", p);
	mark->Load();
	const float x = GetX() - 88 + p * 22;
	mark->ChangePos(x, mark->GetY());
	score->ChangePos(x, score->GetY());
	score->ChangeText(point);
	for (int i = 0; i < 8; i++) {
		if (i < p)
			box[i]->SetAlpha();
		else
			box[i]->SetAlpha(100);
	}
}

void ScoreBar::ContentView() {
	title->View();
	mark->View();
	score->View();
	for (int i = 0; i < 2; i++)
		para[i]->View();
	for (int i = 0; i < 8; i++)
		box[i]->View();
}

ScoreBar::~ScoreBar() {
	delete title;
	delete mark;
	delete score;
	for (int i = 0; i < 2; i++)
		delete para[i];
	for (int i = 0; i < 8; i++)
		delete box[i];
}

TimingBar::TimingBar(Font *font) : ScoreBar(font, HEIGHT * 0.44, "タイミング", "slow", "early") {}

ExpressionBar::ExpressionBar(Font *font) : ScoreBar(font, HEIGHT * 0.54, "表情", "bad", "good") {}

ResultComment::ResultComment(Font *font)
	: Draw(WIDTH * 0.6, HEIGHT * 0.64) {
	title = new MyDrawTextLine(font, "コメント", GetX(), GetY(), 0, 24, WIDTH * 0.55, 2);
	comment = new MyDrawTexts(font, "", GetX(), GetY() + 66, 1, 20, 16);
}
 
void ResultComment::Load(const char *str) {
	comment->ChangeText(str);
}

void ResultComment::ContentView() {
	title->View();
	comment->View();
}

ResultComment::~ResultComment() {
	delete title;
	delete comment;
}

ResultBody::ResultBody(Font *font) 
	: Draw(WIDTH * 0.8, HEIGHT * 0.53) {
	body = new MyDrawGraph(GetX(), GetY(), "img/man.png");
	part[0] = new MyDrawText(font, "左手", GetX() - 106, GetY() - 68, 1, 20);
	part[1] = new MyDrawText(font, "右手", GetX() + 140, GetY() - 55, 1, 20);
	part[2] = new MyDrawText(font, "左足", GetX() - 100, GetY() + 68, 1, 20);
	part[3] = new MyDrawText(font, "右足", GetX() + 122, GetY() + 55, 1, 20);
	point[0] = new MyDrawText(font, "A", GetX() - 147, GetY() - 70, 1, 30, "Yellow");
	point[1] = new MyDrawText(font, "A", GetX() + 99, GetY() - 57, 1, 30, "Yellow");
	point[2] = new MyDrawText(font, "B", GetX() - 141, GetY() + 66, 1, 30, "Yellow");
	point[3] = new MyDrawText(font, "C", GetX() + 81, GetY() + 53, 1, 30, "Yellow");
}

void ResultBody::Load() {
	body->Load();
}

void ResultBody::ContentView() {
	body->View();
	for (int i = 0; i < 4; i++) {
		part[i]->View();
		point[i]->View();
	}
}

ResultBody::~ResultBody() {
	delete body;
	for (int i = 0; i < 4; i++) {
		delete part[i];
		delete point[i];

	}
}

ResultGraph::ResultGraph(Font *font) 
	: Draw(WIDTH * 0.65, HEIGHT * 0.31) {
	float w = WIDTH * 0.6, h = HEIGHT * 0.13;
	int score[10] = { 50, 80, 40, 90, 100, 70, 60, 80, 40, 70 };
	int max = 10;
	for (int i = 0; i < max; i++) {
		float x1 = GetX() - w / 2 + (float)i / (max - 1) * w;
		float y1 = GetY() + h / 2 - (float)score[i] / 100 * h;
		if (i > 0) {
			float x2 = GetX() - w / 2 + (float)(i - 1) / (max - 1) * w;
			float y2 = GetY() + h / 2 - (float)score[i - 1] / 100 * h;
			line[i - 1] = new MyDrawLine(x1, y1, x2, y2, 3);
		}
		dot[i] = new MyDrawCircle(x1, y1, 10, "Yellow");
		if (score[i] > 80)
			dot[i]->SetViewFlag(TRUE);
		else
			dot[i]->SetViewFlag(FALSE);
	}
	frame[0] = new MyDrawLine(GetX() - w / 2, GetY() - h / 2, GetX() - w / 2, GetY() + h / 2, 6, "White");
	frame[1] = new MyDrawLine(GetX() - w / 2, GetY() + h / 2, GetX() + w / 2, GetY() + h / 2, 6, "White");
	scale = new MyDrawTexts(font, "100\n・\n・\n・\n・\n50\n・\n・\n・\n・\n0", GetX() - w / 2 - WIDTH * 0.025, GetY(), 1, 20, 4);
	part[0] = new MyDrawTextV(font, "イントロ", GetX() - w / 2 + WIDTH * 0.05, GetY() + HEIGHT * 0.075, 2, 16);
	part[1] = new MyDrawTextV(font, "Aメロ", GetX() - w / 2 + WIDTH * 0.1, GetY() + HEIGHT * 0.075, 2, 16);
}

void ResultGraph::ContentView() {
	for (int i = 0; i < 2; i++)
		part[i]->View();
	for (int i = 0; i < 9; i++)
			line[i - 1]->View();
	for(int i = 0; i < 10; i++)
		dot[i]->View();

	for (int i = 0; i < 2; i++)
		frame[i]->View();
	scale->View();
}

ResultGraph::~ResultGraph() {
	for (int i = 0; i < 2; i++)
		delete part[i];
	for (int i = 0; i < 10; i++) {
		delete dot[i];
		if (i > 0)
			delete line[i - 1];
	}
	for (int i = 0; i < 2; i++)
		delete frame[i];
	scale->View();
}