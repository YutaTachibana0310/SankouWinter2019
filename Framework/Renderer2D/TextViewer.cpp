//=====================================
//
//TextViewer.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TextViewer.h"
#include "../Resource/FontManager.h"
#include "TextOutLine.h"

/**************************************
�R���X�g���N�^
***************************************/
TextViewer::TextViewer(const char * fontName, int fontSize) :
	font(NULL),
	fontSize(fontSize),
	posX(10),
	posY(10),
	lineNum(1),
	color(0xffffffff),
	text(""),
	useItalic(false),
	useOutline(false),
	horizontal(HorizontalAlignment::Center),
	vertical(VerticalAlignment::Center)
{
	font = FontManager::Instance()->GetFont(fontName, fontSize);
	italicFont = FontManager::Instance()->GetItalicFont(fontName, fontSize);

	outline = new OutLine(this);
}

/**************************************
�f�X�g���N�^
***************************************/
TextViewer::~TextViewer()
{
	SAFE_RELEASE(font);
	SAFE_RELEASE(italicFont);
	SAFE_DELETE(outline);
}

/**************************************
�`�揈��
***************************************/
void TextViewer::Draw(void)
{
	if (!active)
		return;

	D3DXVECTOR3 position = transform->GetPosition();
	posX = (int)position.x;
	posY = (int)position.y;

	//�A�E�g���C���`��
	if (useOutline)
	{
		outline->Draw();
	}

	//�`��
	RECT rect = GetRect();

	if(!useItalic)
		font->DrawText(NULL, text.c_str(), -1, &rect, (WORD)horizontal | (WORD)vertical | DT_NOCLIP, color);
	else
		italicFont->DrawText(NULL, text.c_str(), -1, &rect, (WORD)horizontal | (WORD)vertical | DT_NOCLIP, color);
}

/**************************************
���W�Z�b�g����
***************************************/
void TextViewer::SetPos(int x, int y)
{
	transform->SetPosition({ (float)x, (float)y, 0.0f });
}

/**************************************
���W�Z�b�g����
***************************************/
void TextViewer::SetColor(const D3DXCOLOR & color)
{
	this->color = color;
}

/**************************************
�e�L�X�g�Z�b�g����
***************************************/
void TextViewer::SetText(const std::string & message)
{
	//���s���������čs�����Z�b�g
	lineNum = 1 + (std::count(message.cbegin(), message.cend(), '\n'));

	text = message;
}

/**************************************
�e�L�X�g�擾����
***************************************/
std::string TextViewer::GetText() const
{
	return text;
}

/**************************************
�C�^���b�N�g�p�ݒ�
***************************************/
void TextViewer::UseItalic(bool state)
{
	useItalic = state;
}

/**************************************
�A�E�g���C���g�p�ݒ�
***************************************/
void TextViewer::UseOutLine(bool state)
{
	useOutline = state;
}

/**************************************
���������̃��C�A�E�g�ݒ�
***************************************/
void TextViewer::SetHorizontalAlignment(HorizontalAlignment alignment)
{
	horizontal = alignment;
}

/**************************************
���������̃��C�A�E�g�ݒ�
***************************************/
void TextViewer::SetVerticalAlignment(VerticalAlignment alignment)
{
	vertical = alignment;
}

/**************************************
�A�E�g���C���̕��ݒ�
***************************************/
void TextViewer::SetOutlineWidth(int width)
{
	outline->SetWidth(width);
}

/**************************************
�A�E�g���C���̃J���[�ݒ�
***************************************/
void TextViewer::SetOutlineColor(const D3DXCOLOR & color)
{
	outline->SetColor(color);
}

/**************************************
Rect�v�Z����
***************************************/
RECT TextViewer::GetRect() const
{
	//�e�L�X�g�𒆉��񂹂ŕ\�����邽�߂�Rect���v�Z
	LONG top = posY - fontSize / 2 * lineNum;
	LONG bottom = top + fontSize * lineNum;

	LONG left = posX;

	//NOTE:���s�ɑΉ����ĂȂ�
	if (horizontal == HorizontalAlignment::Center)
		left -= text.length() * fontSize / 2;
	else if (horizontal == HorizontalAlignment::Right)
		left -= text.length() * fontSize;

	LONG right = posX;

	if (horizontal == HorizontalAlignment::Center)
		right += text.length() * fontSize / 2;
	else if (horizontal == HorizontalAlignment::Left)
		right += text.length() * fontSize;

	return { left, top, right, bottom};
}
