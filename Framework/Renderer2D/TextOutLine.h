//=====================================
//
// TextOutLine.h
// �@�\:�e�L�X�g�A�E�g���C��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TEXTOUTLINE_H_
#define _TEXTOUTLINE_H_

#include "../../main.h"
#include "TextViewer.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TextViewer::OutLine
{
public:
	OutLine(const TextViewer* entity);
	~OutLine();

	void Draw();

	void SetColor(const D3DXCOLOR& color);

	void SetWidth(int width);

private:
	const TextViewer* entity;

	D3DXCOLOR color;
	int width;
};

#endif