#ifndef __SONGSELECTCOMMON_H_INCLUDED__
#define __SONGSELECTCOMMON_H_INCLUDED__

#include "DxLib.h"
#include "Draw.h"
#include "Common.h"
#include "Touch.h"
#include "Song.h"
#include "Font.h"

#define BACK_TOP -2
#define BACK -1
#define MAIN 0
#define MODE 1
#define OPTION1 2
#define OPTION2 3

//�ȑI����ʃ^�C�g��
class SongSelectTitle {
public:
	SongSelectTitle(Font *font); //������
	void Update(int scene); //�v�Z
	void View(); //�\��
	~SongSelectTitle();
private:
	MyDrawText *myDrawText;
	MyDrawText *subTitle;
	MyDrawLine *myDrawLine;
};

//�ȑI����ʃJ�o�[�֌W
class SongSelectCover {
public:
	SongSelectCover(Font *font); //������
	void View(); //�\��
	void Update(Touch *touch);
	~SongSelectCover();
private:
	int n, now;
	boolean drawFlag;
	Song *song[256];
	MyDrawGraph *grad[2]; //�J�o�[�摜
	MyDrawGraph *box; //�J�o�[�摜
	MyDrawBox *myDrawBox;
};

#endif