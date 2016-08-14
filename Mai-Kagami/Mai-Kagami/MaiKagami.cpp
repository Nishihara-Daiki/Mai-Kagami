#include "MaiKagami.h"

MaiKagami::MaiKagami() {
	touch = new Touch();
	scene = START; //シーン初期化
	font = new Font();
	songs = new Songs(font); //曲一覧作成
	top = new Top(font);
	songSelect = new SongSelect(font, touch, songs);
	throughMain = new ThroughMain(font, touch, songs);
}

//全体の算計
void MaiKagami::Update() {
	touch->Check();
	switch (scene) {
	case TOP:
		scene = top->Switch(scene);
		break;
	case SONG_SELECT:
		scene = songSelect->Switch(scene);
		break;
	case THROUGH:
		scene = throughMain->Update();
		break;
	}

	top->Update(scene); //トップ画面計算

	switch (scene) {
	case TOP:
		break;
	case SONG_SELECT:
		songSelect->Update(scene); //曲選択画面計算
		break;
	case THROUGH:
		break;
	}
}

//全体の描画
void MaiKagami::View() {
	top->View(); //トップ画面表示

	switch (scene) {
	case TOP:
		break;
	case SONG_SELECT:
		songSelect->View();
		break;
	case THROUGH:
		throughMain->View();
		break;
	}
}