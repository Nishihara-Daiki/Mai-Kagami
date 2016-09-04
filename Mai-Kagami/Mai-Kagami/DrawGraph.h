#ifndef __DRAWGRAPH_H_INCLUDED__
#define __DRAWGRAPH_H_INCLUDED__

#include "DxLib.h"
#include "Draw.h"
#include <string>

//画像関係
class MyDrawGraph : public Draw{
public:
	MyDrawGraph(const char *fileName); //初期化
	MyDrawGraph(const float x, const float y, const char *fileName, const double ExRate = 1.0); //初期化
	void ContentView(); //表示
	void Load();
	void ChangeEx(const double ExRate); //倍率変更
	double GetEx();
	void SetExAnimation(double target_ex, Easing ease = LINER);
	void Update();
	void Release();
protected:
	std::string fileName; //ファイル名
	int handle; //画像用ハンドル
	double ex; //表示倍率
	double target_ex, default_ex;
	Easing ease_ex;
};

//動画関係
class MyDrawMovie : public MyDrawGraph {
public:
	MyDrawMovie(const char *filename); //初期化
	MyDrawMovie(const float x, const float y, const char *filename, const double ExRate); //初期化
	void ContentView(); //表示
	void Seek(const int flame = -1); //指定したフレームに移動
	void Start(); //再生
	void Stop(); //停止
	void ChangeSpeed(double speed); //スピード変更
	void SetSpeed(); //スピードセット
	void SetPart(); //区間セット
	double GetSpeed(); //スピード取得
	int GetStartFlame(); //最初のフレーム数取得
	int GetEndFlame(); //最後のフレーム数取得
	int GetNowFlame(); //現在のフレーム数取得
	int GetAllFlame(); //動画のフレームズ数取得
	void SetStartFlame(const int flame = 0); //スタートフレーム指定
	void SetEndFlame(const int flame = -1); //エンドフレーム指定
	~MyDrawMovie();
private:
	double speed, sp;
	int startFlame = 0, endFlame = -1, sf, ef;
};

#endif