#include "CommonText.h"

//タイトル表示用
DrawTitle::DrawTitle(Font *font, const char *str) 
	: MyDrawTextLine(font, str, WIDTH * 0.65, HEIGHT * 0.21, 1, 50, WIDTH * 0.4, 3, sceneOpacity) {}

//サブタイトル表示用
DrawSubtitle::DrawSubtitle(Font *font, const char *str)
	: MyDrawText(font, str, WIDTH * 0.65, HEIGHT * 0.25, 1, 30, sceneOpacity) {}