#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#define SIZE_RATE	2
#define WIDTH		1080
#define HEIGHT		1920

#define NFC_POS		HEIGHT * 0.85
#define NFC_FLAG	FALSE	//NFCÉJÅ[ÉhÇì«Ç›çûÇﬁÇ©Ç«Ç§Ç©(TRUE:ì«Ç›çûÇﬁ/FALSE:ì«Ç›çûÇ‹Ç»Ç¢)

typedef enum {
	TOP,
	SONG_SELECT,
	THROUGH,
	THROUGH_RESULT,
	PART,
	PART_RESULT,
	THROUGH_OPTION,
	PART_OPTION
} MainScene;

#endif