#include "ThroughResult.h"

ThroughResult::ThroughResult(Font *font, Songs *songs, Touch *touch) {
	this->songs = songs;
	title        = new MyDrawTextLine(font, "採点結果", WIDTH * 0.5, 
									  HEIGHT * 0.15, 1, 60, WIDTH * 0.5, 4);						//採点結果
	circle       = new MyDrawCircle(WIDTH * 0.5, HEIGHT * 0.5, WIDTH * 0.3, 10, "WHITE");			//縁が白色の円
	pointCircle  = new MyDrawCircleGauge(WIDTH * 0.5, HEIGHT * 0.5, WIDTH * 0.3, 58, 6);			//青色の弧
	pointCircle2 = new MyDrawCircle(pointCircle->GetEndX() * SIZE_RATE, 
									pointCircle->GetEndY() * SIZE_RATE, 16);						//弧の先の円
	button       = new CircleButton2(font, touch, "次へ", 4);										//次へボタン
	text         = new MyDrawText(font, "総合得点", WIDTH * 0.5, HEIGHT * 0.42, 1, 46, "White");	//「総合得点」
	point1       = new MyDrawGraph(WIDTH * 0.42, HEIGHT * 0.51, "img/5.png", 0.23);					//得点(十の位)	
	point2       = new MyDrawGraph(WIDTH * 0.51, HEIGHT * 0.51, "img/8.png", 0.23);					//得点(一の位)
	unit         = new MyDrawText(font, "点", WIDTH * 0.58, HEIGHT * 0.54, 0, 46, "White");			//「点」
	last         = new MyDrawText(font, "前回 --点", WIDTH * 0.5, HEIGHT * 0.58, 1, 36, "White");	//前回の点数
}

void ThroughResult::Load() {
	point1->Load();		//得点の十の位の画像を読み込み
	point2->Load();		//得点の一の位の画像を読み込み

	song = songs->GetSong(songs->GetNowSong()); //現在選択中の曲を取得
	song->coverGraph->Load(); //曲カバー画像をロード
	song->coverGraph->ChangePos(WIDTH * 0.3, HEIGHT * 0.26); //カバー画像の表示位置変更
	song->drawSongTitle->ChangePos(WIDTH * 0.6, HEIGHT * 0.24); //曲タイトルの表示位置変更
}

ThroughResultScene ThroughResult::Switch(const ThroughResultScene scene) {
	if (button->GetTouch() == 1) //ボタンが押されたら
		return THROUGH_RESULT_DETAIL; //詳細ページに飛ぶ
	return scene;
}

void ThroughResult::ContentUpdate() {
	if (nowScene == THROUGH_RESULT_TOP) //シーンがTHROUGH_RESULT_TOPだったら
		viewFlag = TRUE; //画面を表示
	else //それ以外は
		viewFlag = FALSE; //画面を非表示
}

void ThroughResult::ContentView() {
	title->View();					//タイトル表示
	song->coverGraph->View();		//曲カバー画像表示
	song->drawSongTitle->View();	//曲タイトル表示
	circle->View();					//白色の円表示
	pointCircle->View();			//青色の弧を表示
	pointCircle2->View();			//弧の先の円を表示
	text->View();					//「総合得点」表示
	point1->View();					//得点(10の位)表示
	point2->View();					//得点(1の位)表示
	unit->View();					//「点」を表示
	last->View();					//前回の得点を表示
	button->View();					//ボタンを表示
}

ThroughResult::~ThroughResult() {
	delete title;					//タイトル削除
	delete circle;					//曲カバー画像削除
	delete pointCircle;				//青色の弧削除
	delete pointCircle2;			//弧の先の円削除
	delete button;					//ボタンを削除
	delete text;					//「総合得点」削除
	delete point1;					//得点(10の位)削除
	delete point2;					//得点(1の位)削除
	delete unit;					//「点」を削除
	delete last;					//前回の得点削除
}