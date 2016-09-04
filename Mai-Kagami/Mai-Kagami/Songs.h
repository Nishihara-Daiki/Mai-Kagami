#ifndef __SONGS_H_INCLUDED__
#define __SONGS_H_INCLUDED__

#include <Windows.h>
#include <winhttp.h>
#include <wchar.h>

#include "Song.h"
#include "DxLib.h"
#include "DrawGraph.h"
#include "Font.h"

#pragma comment (lib, "winhttp.lib")

class Songs {
public:
	Songs(Font *font);
	int GetSongNum(); //曲数取得
	Song *GetSong(int x);
	int GetNowSong();
	//履歴ロード
	//成功したら0,エラーならば-1を返す
	int LoadHistory(const char *userId);
private:
	Song *song[256];
	int Search(const int songId);
	int n; //曲数
};

#endif