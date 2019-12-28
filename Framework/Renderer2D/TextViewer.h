//=====================================
//
//TextViewer.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_

#include "../../main.h"

#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TextViewer : public GameObject
{
public:
	
	//���������̃��C�A�E�g
	enum class HorizontalAlignment
	{
		Left = 0x00,		//����
		Center = 0x01,		//������
		Right = 0x02		//�E��
	};

	//���������̃��C�A�E�g
	enum class VerticalAlignment
	{
		Top = 0x00,			//���
		Center = 0x04,		//������
		Bottom = 0x08		//����
	};
	
	//�R���X�g���N�^
	//fontName : �g�p����t�H���g�̖��O ���t�H���g�t�@�C���ւ̃p�X�ł͂Ȃ��̂Œ���
	//size : �\���t�H���g�T�C�Y
	TextViewer(const char* fontName, int size);

	//�f�X�g���N�^
	~TextViewer();

	//�`�揈��
	void Draw(void);

	//���W�Z�b�g����
	void SetPos(int x, int y);

	//�J���[�Z�b�g����
	void SetColor(const D3DXCOLOR& color);

	//�\���e�L�X�g�Z�b�g����
	void SetText(const std::string& message);

	//�\���e�L�X�g�擾����
	std::string GetText() const;

	//�C�^���b�N�g�p�ݒ�
	void UseItalic(bool state);

	//�A�E�g���C���g�p�ݒ�
	void UseOutLine(bool state);

	//���������̃��C�A�E�g�ݒ�
	void SetHorizontalAlignment(HorizontalAlignment alignment);

	//���������̃��C�A�E�g�ݒ�
	void SetVerticalAlignment(VerticalAlignment alignment);

	//�A�E�g���C���̕��ݒ�
	void SetOutlineWidth(int width);

	//�A�E�g���C���̃J���[�ݒ�
	void SetOutlineColor(const D3DXCOLOR& color);

private:
	//�t�H���g�C���^�[�t�F�C�X
	LPD3DXFONT font;
	LPD3DXFONT italicFont;

	//�t�H���g�T�C�Y
	int fontSize;

	//�\�����W
	int posX;
	int posY;

	//�s��
	int lineNum;

	//�\���J���[
	D3DXCOLOR color;

	//�C�^���b�N�g�p
	bool useItalic;

	//�A�E�g���C���g�p
	bool useOutline;

	//���C�A�E�g
	HorizontalAlignment horizontal;
	VerticalAlignment vertical;

	//�\��������
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif

	//Rect�v�Z����
	RECT GetRect() const;

	//�A�E�g���C���p�����N���X
	class OutLine;
	OutLine* outline;
};

#endif