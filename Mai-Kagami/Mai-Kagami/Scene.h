#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DURATION 10  // ��ʐ؂�ւ��ɂ����鎞��

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
	boolean CheckView(); //�\�������ǂ����m�F����(TRUE:�\�����AFALSE�F��\����)
protected:
	int nowScene;
	long fadeCount = 0;	// ��ʐ؂�ւ����̃t�F�[�h�C���E�A�E�g�̃J�E���^
	virtual void ContentView() = 0; //�\���ڍ�
	virtual void ContentUpdate() = 0; //�X�V�ڍ�
	void UpdateViewFlag(boolean flag, long duration = SCENE_DURATION, long delay = 0);
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
	boolean deleteFlag = FALSE;	// �폜�m�F�p (FALSE:���폜(�ʏ�) / TRUE:�폜��)
};

typedef struct {
public:
	void SetOpacity(const double opacity) { this->opacity = opacity; };
	double GetDrawOpacity() { return opacity; };
private:
	double opacity = 1.0;
} SceneSwitch;

extern SceneSwitch gSceneSwitch;

#endif