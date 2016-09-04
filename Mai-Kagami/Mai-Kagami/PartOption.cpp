#include "PartOption.h"

PartOptionPreview2::PartOptionPreview2(Font *font, Songs *songs, Touch *touch) 
	: PartOptionPreview(font, songs, touch, OPTION2, OPTION2_PART, OPTION2_SPEED) {
	button[0] = new CircleButton(font, touch, "スタート!", 3, WIDTH * 0.8);
	button[1] = new CircleButton2(font, touch, "戻る", 4);
}

int PartOptionPreview2::Switch(const int scene) {
	if (button[0]->GetTouch() == 1) {
		Song *song = songs->GetSong(songs->GetNowSong());
		song->danceMovie->SetPart();
		return NEXT2;
	}
	if (button[1]->GetTouch() == 1)
		return MODE;
	return PartOptionPreview::Switch(scene);
}

void PartOptionPreview2::ContentView() {
	for (int i = 0; i < 2; i++)
		button[i]->View();
	PartOptionPreview::ContentView();
}

PartOptionPreview2::~PartOptionPreview2() {
	for (int i = 0; i < 2; i++)
		delete button[i];
}

PartOptionButton::PartOptionButton(Font *font, Songs *songs, Touch *touch) 
	: PartOptionPop(font, songs, touch, OPTION2, OPTION2_PART, OPTION2_SPEED, new PartOptionPreview2(font, songs, touch)) {}