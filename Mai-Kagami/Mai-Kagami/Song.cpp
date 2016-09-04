#include "Song.h"

//履歴セット
void SongHistory::Set(const int history[2]) {
	for (int i = 0; i < 2; i++)
		this->history[i] = history[i];
}

//履歴取得
void SongHistory::Get(int *history[2]) {
	for (int i = 0; i < 2; i++)
		*history[i] = this->history[i];
}

//曲名、アーティスト情報
DrawSongTitle::DrawSongTitle(Font *font, const char *title, const char *artist) {
	songTitle = new MyDrawTextLine(font, title,0, 0, 1, 30, WIDTH * 0.35, 2); //テキスト初期化
	songArtist = new MyDrawText(font, artist, 0, 0, 2, 20); //テキスト初期化
}

void DrawSongTitle::ChangePos(const float x, const float y) {
	Pos::ChangePos(x, y);
	songTitle->ChangePos(x, y);
	songArtist->ChangePos(x + WIDTH * 0.17, y + HEIGHT * 0.025);
}

void DrawSongTitle::View() {
	songTitle->View();
	songArtist->View();
}

DrawSongTitle::~DrawSongTitle() {
	delete songTitle;
	delete songArtist;
}

//パート情報
void SongPart::Set(const int flame, const char *name) {
	this->flame = flame;
	strcpy_s(this->name, sizeof(this->name), name);
}


//フレーム数取得
int SongPart::GetFlame() {
	return flame;
}

//パート名取得
char *SongPart::GetName() {
	return name;
}

Song::Song(Font *font, const int id, const char *title, const char *artist, const char *folder) {
	char cover[256], movie[256];
	strcpy_s(Song::folder, sizeof(Song::folder), folder); //フォルダ
	sprintf_s(cover, sizeof(cover), "song/%s/cover.jpg", folder); //カバー画像
	sprintf_s(music, sizeof(music), "song/%s/music.mp3", folder); //音楽
	sprintf_s(movie, sizeof(movie), "song/%s/movie.ogv", folder); //動画
	Song::id = id;
	n = new int();
	songPartNum = new int();
	start = new int();
	end = new int();
	*start = 0;
	*end = 0;
	for(int i = 0; i < 256; i++)
		songPart[i] = new SongPart();

	drawSongTitle = new DrawSongTitle(font, title, artist);
	coverGraph = new MyDrawGraph(cover);
	coverWhite = new MyDrawGraph("img/box.png");
	danceMovie = new MyDrawMovie(movie);
	songHistory = new SongHistory();
}

//曲IDを取得
int Song::GetSongId() {
	return id;
}

//現在の位置IDを取得
int Song::GetNow() {
	return *n;
}

//位置IDをセット
void Song::SetNow(const int n) {
	*Song::n = n;
}

//動画の再生スピードを変更
void Song::ChangeSpeed(int num) {
	const double s[6] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5 };
	static int x = 0;
	if (num == 1 && x > 0) {
		x -= 1;
		danceMovie->ChangeSpeed(s[x]);
	}
	if (num == -1 && x < 5) {
		x += 1;
		danceMovie->ChangeSpeed(s[x]);
	}
}

//動画の開始位置を変更
void Song::ChangeStart(int num) {
	if (num == 1 && *start > 0)
		(*start) -= 1;
	if (num == -1 && *start < *end)
		(*start) += 1;
	danceMovie->SetStartFlame(GetPart(*start)->GetFlame());
}

//動画の終了位置を変更
void Song::ChangeEnd(int num) {
	if (num == 1 && *end > *start)
		(*end) -= 1;
	if (num == -1 && *end < GetPartNum() - 1)
		(*end) += 1;

	if (*end + 1 == GetPartNum())
		danceMovie->SetEndFlame(danceMovie->GetAllFlame());
	else
		danceMovie->SetEndFlame(GetPart(*end + 1)->GetFlame());

}

int Song::StartPart() {
	return *start;
}

int Song::EndPart() {
	return *end;
}

//パート情報をロード
void Song::LoadPart() {
	char part[256];
	sprintf_s(part, sizeof(part), "song/%s/part.csv", folder);
	SetUseASyncLoadFlag(FALSE);
	int file = FileRead_open(part, FALSE);
	SetUseASyncLoadFlag(TRUE);
	char buf[256];
	int flame;
	*songPartNum = 0;
	while (FileRead_scanf(file, "%d,%[^\n\r]", &flame, buf) != EOF) {
		songPart[*songPartNum]->Set(flame, buf);
		(*songPartNum)++;
	}
}

//パート情報取得
SongPart *Song::GetPart(int num) {
	return songPart[num];
}

//パート数取得
int Song::GetPartNum() {
	return *songPartNum;
}