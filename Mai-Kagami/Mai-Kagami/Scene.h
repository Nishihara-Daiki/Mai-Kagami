#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DURATION	10	// ��ʐ؂�ւ��t�F�[�h�A�j���[�V��������
#define SCENE_IN_WAIT	10	// ��ʐ؂�ւ��t�F�[�h�C���܂ł̑҂�����

enum {
	NOT_FADE,	// ��ʐ؂�ւ����ł͂Ȃ�
	FADING_IN,	// �t�F�[�h�C����
	FADING_OUT,	// �t�F�[�h�A�E�g��
	FADE_WAIT,	// �t�F�[�h�C���E�A�E�g�J�n�܂ł̑҂�
};

enum {
	UNLOADED,	// �����[�h
	THREADING,	// ���Ă��X���b�h�̌v�Z��
	LOADING,	// �摜���[�h��
	LOADED,		// ����
};

// ��ʒ�`
class Scene {
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
	void UpdateViewFlag(boolean flag, long wait = 0, long duration = SCENE_DURATION);
private:
	boolean viewFlag = FALSE;		//�\���p�t���O(TRUE:�\���AFALSE�F��\��)
	short fadeStatus = NOT_FADE;	// ��ʐ؂�ւ��̏��
	double sceneOpacity = 1.0;
	virtual void SetOpacity(double opacity) = 0;
};

class SubScene : public Scene {
private:
	void SetOpacity(double opacity);
};

//��ʒ�`
class MainScene : public Scene {
protected:
	void Load(); //���[�h
	void Delete(); //�폜
	void SetDeleteFlag(boolean status);
private:
	void SetOpacity(double opacity);
	virtual void ContentLoad() = 0; //���[�h�ڍ�
	virtual void ContentDelete() = 0; //�폜�ڍ�
	int loadStatus = UNLOADED; //���[�h�m�F�p�i0�F�����[�h�A1�F���[�h���A2�F���[�h�����j
	boolean deleteFlag = FALSE;	// �폜�m�F�p (FALSE:���폜(�ʏ�) / TRUE:�폜��)
};

typedef struct {
public:
	void SetSubOpacity(const double opacity) { subOpacity = opacity; };
	void SetMainOpacity(const double opacity) { mainOpacity = opacity; };
	double GetDrawOpacity() { return mainOpacity * subOpacity; };
private:
	double subOpacity = 1.0;
	double mainOpacity = 1.0;
} SceneSwitch;

extern SceneSwitch gSceneSwitch;

#endif