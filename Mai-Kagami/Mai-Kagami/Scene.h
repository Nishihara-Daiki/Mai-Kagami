#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DELAY 10  // ��ʐ؂�ւ��ɂ����鎞��

enum {
	NOT_FADE,	// ��ʐ؂�ւ����ł͂Ȃ�
	FADING_IN,	// �t�F�[�h�C����
	FADING_OUT,	// �t�F�[�h�A�E�g��
};

//�T�u��ʒ�`
class SubScene {
public:
	void Update(const int scene); //�X�V
	void View(); //�\��
	void Load(); //���[�h
	void Delete(); //�폜
//	void SetDelay(long);
	boolean CheckView(); //�\�������ǂ����m�F����(TRUE:�\�����AFALSE�F��\����)
protected:
	int nowScene;
	long delayCount = 0;	// ��ʐ؂�ւ����̃f�B���C
	virtual void ContentView() = 0; //�\���ڍ�
	virtual void ContentUpdate() = 0; //�X�V�ڍ�
	void UpdateViewFlag(boolean flag, long delay = SCENE_DELAY);
private:
	boolean viewFlag = FALSE;		//�\���p�t���O(TRUE:�\���AFALSE�F��\��)
	short fadeStatus = NOT_FADE;	// ��ʐ؂�ւ��̏��
	double sceneOpacity = 1.0;
};

//��ʒ�`
class Scene : public SubScene {
protected:
	void Load(); //���[�h
	void Delete(); //�폜
	void SetDeleteFlag(boolean status);
private:
	virtual void ContentLoad() = 0; //���[�h�ڍ�
	virtual void ContentDelete() = 0; //�폜�ڍ�
	int loadFlag = 0; //���[�h�m�F�p�i0�F�����[�h�A1�F���[�h���A2�F���[�h�����j
	int deleteFlag = FALSE;	// �폜�m�F�p (FALSE:���폜(�ʏ�) / TRUE:�폜��)
};

typedef struct {
public:
	void SetOpacity(const double opacity) {
		//switch (fadeStatus) {
		//	case FADING_IN:  fadeInOpacity = opacity; break;
		//	case FADING_OUT: fadeOutOpacity = opacity; break;
		//	default: fadeInOpacity = fadeOutOpacity = 1.0; break;
		//}
		this->opacity = opacity;
	};
	//double GetOpacity() { return opacity; };
	double GetDrawOpacity() {
		//switch (fadeStatus) {
		//	case NOT_FADE:   return 1.0;
		//	case FADING_IN:  return fadeInOpacity;
		//	case FADING_OUT: return fadeOutOpacity;
		//}
		return opacity;
	};
	//void FadeStatus(short flag) { fadeStatus = flag; };
private:
	//double fadeInOpacity = 1.0;
	//double fadeOutOpacity = 1.0;
	double opacity = 1.0;
	//short fadeStatus;
} SceneSwitch;

extern SceneSwitch gSceneSwitch;

#endif