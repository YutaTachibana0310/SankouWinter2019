//=====================================
//
// TextOutLine.cpp
// �@�\:�e�L�X�g�A�E�g���C��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TextOutLine.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TextViewer::OutLine::OutLine(const TextViewer * entity) :
	entity(entity),
	color(D3DXCOLOR(0.05f, 0.05f, 0.05f, 1.0f)),
	width(2)
{
}

/**************************************
�f�X�g���N�^
***************************************/
TextViewer::OutLine::~OutLine()
{
}

/**************************************
�`�揈��
***************************************/
void TextViewer::OutLine::Draw()
{
	RECT rect = entity->GetRect();

	rect.left -= width;
	entity->font->DrawTextA(NULL, entity->text.c_str(), -1, &rect, (WORD)entity->horizontal | (WORD)entity->vertical | DT_NOCLIP, color);

	rect.left += width * 2;
	entity->font->DrawTextA(NULL, entity->text.c_str(), -1, &rect, (WORD)entity->horizontal | (WORD)entity->vertical | DT_NOCLIP, color);

	rect.left -= width;
	rect.top -= width;
	entity->font->DrawTextA(NULL, entity->text.c_str(), -1, &rect, (WORD)entity->horizontal | (WORD)entity->vertical | DT_NOCLIP, color);

	rect.top += width * 2;
	entity->font->DrawTextA(NULL, entity->text.c_str(), -1, &rect, (WORD)entity->horizontal | (WORD)entity->vertical | DT_NOCLIP, color);
}

/**************************************
�F�ݒ菈��
***************************************/
void TextViewer::OutLine::SetColor(const D3DXCOLOR & color)
{
	this->color = color;
}

/**************************************
�����ݒ菈��
***************************************/
void TextViewer::OutLine::SetWidth(int width)
{
	this->width = width;
}
