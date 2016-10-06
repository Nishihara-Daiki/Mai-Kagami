#include "PartPlay.h"

PartStart::PartStart(Font *f)
	: StartSceen(f, PART_START, PART_PLAY, PART_PAUSE) {}

//•”•ª—ûK‰æ–Ê
PartPlay::PartPlay(Font *font, Songs *songs, Touch *touch)
	: PlayScreen(font, songs, touch, PART_START, PART_COUNTDOWN, PART_PLAY, PART_NEXT) {}