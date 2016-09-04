#include "DrawGraph.h"


//画像初期化(座標指定なし、あとから指定する場合)
//MyDrawGraph（ファイル名）
MyDrawGraph::MyDrawGraph(const char *fileName) {
	ex = 1.0;
	this->fileName = fileName;
}

//画像初期化
//MyDrawGraph（x座標、y座標、ファイル名、拡大率） //拡大率は省略可能、省略した場合等倍
MyDrawGraph::MyDrawGraph(const float x, const float y, const char *fileName, const double ExRate) : Draw(x, y) {
	ex = ExRate;
	this->fileName = fileName;
}

//画像ロード
void MyDrawGraph::Load() {
	handle = LoadGraph(fileName.c_str()); // 画像のロード
}

//画像表示
void MyDrawGraph::ContentView() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DrawRotaGraphF(x, y, ex / SIZE_RATE, 0, handle, TRUE, FALSE); //描画
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

//画像大きさ変更
void MyDrawGraph::ChangeEx(const double ExRate) {
	ex = ExRate;
}
//画像大きさ取得
double MyDrawGraph::GetEx() {
	return ex;
}

void MyDrawGraph::SetExAnimation(double target_ex, Easing ease) {
	if (GetTime() != 0)
		return;
	default_ex = GetEx();
	this->target_ex = target_ex;
	ease_ex = ease;
}

void MyDrawGraph::Update() {
	double r = UpdateRate(ease_ex);
	float nex = default_ex + (target_ex - default_ex) * r;
	ChangeEx(nex);
	Draw::Update();
}

//画像を解放
void MyDrawGraph::Release() {
	DeleteGraph(handle);
}

//動画初期化
MyDrawMovie::MyDrawMovie(const char *filename) : MyDrawGraph(filename) {
	speed = sp = 1.0;
}

//動画初期化
MyDrawMovie::MyDrawMovie(const float x, const float y, const char *filename, const double ExRate)
	: MyDrawGraph(x, y, filename, ExRate) {
	speed = sp = 1.0;
}

//動画表示
void MyDrawMovie::ContentView() {
	if (!CheckHandleASyncLoad(handle)) {
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraphF(x, y, ex / SIZE_RATE, 0, handle, TRUE, TRUE); //描画
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}

//指定したフレームに移動
void MyDrawMovie::Seek(const int flame) {
	Stop();
	if(flame == -1)
		SeekMovieToGraphToFrame(handle, startFlame);
	else
		SeekMovieToGraphToFrame(handle, flame);
}

//再生
void MyDrawMovie::Start() {
	if (!CheckHandleASyncLoad(handle)) {
		SetSpeed();
		if (GetNowFlame() == GetEndFlame())
			Seek();
		if(GetMovieStateToGraph(handle) == 0)
			PlayMovieToGraph(handle);
	}
}

//再生停止
void MyDrawMovie::Stop() {
	PauseMovieToGraph(handle);
}

//スピード変更
void MyDrawMovie::ChangeSpeed(double speed) {
	this->sp = speed;
}

//スピードセット
void MyDrawMovie::SetSpeed() {
	if (speed != sp) {
		Stop();
		Seek();
		speed = sp;
		SetPlaySpeedRateMovieToGraph(handle, speed);
	}
}

void MyDrawMovie::SetPart() {
	if (sf != startFlame || ef != endFlame) {
		startFlame = sf;
		endFlame = ef;
		Stop();
		Seek();
	}
}

//スピード取得
double MyDrawMovie::GetSpeed() {
	return sp;
}

//最初のフレーム数取得
int MyDrawMovie::GetStartFlame() {
	return startFlame;
}

//最後のフレーム数取得
int MyDrawMovie::GetEndFlame() {
	if (endFlame == -1)
		return GetAllFlame();
	return endFlame;
}

//現在のフレーム数取得
int MyDrawMovie::GetNowFlame() {
	return TellMovieToGraphToFrame(handle);
}

//動画のフレーム数取得
int MyDrawMovie::GetAllFlame() {
	return GetMovieTotalFrameToGraph(handle) - 1;
}

//スタートフレーム指定
void MyDrawMovie::SetStartFlame(const int flame) {
	sf = flame;
}

//エンドフレーム指定
void MyDrawMovie::SetEndFlame(const int flame) {
	ef = flame;
}

MyDrawMovie::~MyDrawMovie() {
	DeleteGraph(handle);
}