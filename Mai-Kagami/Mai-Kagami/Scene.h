#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "DxLib.h"
#include "Main.h"

#define SCENE_DELAY 120  // ��ʐ؂�ւ��ɂ����鎞��

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
	long delay = 0;	// ��ʐ؂�ւ����̃f�B���C
	double sceneOpacity = 1.0;
	virtual void ContentView() = 0; //�\���ڍ�
	virtual void ContentUpdate() = 0; //�X�V�ڍ�
	void UpdateViewFlag(boolean flag, long delay = SCENE_DELAY);
private:
	boolean viewFlag = FALSE; //�\���p�t���O(TRUE:�\���AFALSE�F��\��)
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

#endif