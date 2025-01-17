//=====================================
//
//TextViewer.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TextViewer.h"
#include "../Resource/FontManager.h"
#include "TextOutLine.h"

/**************************************
コンストラクタ
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
デストラクタ
***************************************/
TextViewer::~TextViewer()
{
	SAFE_RELEASE(font);
	SAFE_RELEASE(italicFont);
	SAFE_DELETE(outline);
}

/**************************************
描画処理
***************************************/
void TextViewer::Draw(void)
{
	if (!active)
		return;

	D3DXVECTOR3 position = transform->GetPosition();
	posX = (int)position.x;
	posY = (int)position.y;

	//アウトライン描画
	if (useOutline)
	{
		outline->Draw();
	}

	//描画
	RECT rect = GetRect();

	if(!useItalic)
		font->DrawText(NULL, text.c_str(), -1, &rect, (WORD)horizontal | (WORD)vertical | DT_NOCLIP, color);
	else
		italicFont->DrawText(NULL, text.c_str(), -1, &rect, (WORD)horizontal | (WORD)vertical | DT_NOCLIP, color);
}

/**************************************
座標セット処理
***************************************/
void TextViewer::SetColor(const D3DXCOLOR & color)
{
	this->color = color;
}

/**************************************
テキストセット処理
***************************************/
void TextViewer::SetText(const std::string & message)
{
	//改行を検索して行数をセット
	lineNum = 1 + (std::count(message.cbegin(), message.cend(), '\n'));

	text = message;
}

/**************************************
テキスト取得処理
***************************************/
std::string TextViewer::GetText() const
{
	return text;
}

/**************************************
イタリック使用設定
***************************************/
void TextViewer::UseItalic(bool state)
{
	useItalic = state;
}

/**************************************
アウトライン使用設定
***************************************/
void TextViewer::UseOutLine(bool state)
{
	useOutline = state;
}

/**************************************
水平方向のレイアウト設定
***************************************/
void TextViewer::SetHorizontalAlignment(HorizontalAlignment alignment)
{
	horizontal = alignment;
}

/**************************************
垂直方向のレイアウト設定
***************************************/
void TextViewer::SetVerticalAlignment(VerticalAlignment alignment)
{
	vertical = alignment;
}

/**************************************
アウトラインの幅設定
***************************************/
void TextViewer::SetOutlineWidth(int width)
{
	outline->SetWidth(width);
}

/**************************************
アウトラインのカラー設定
***************************************/
void TextViewer::SetOutlineColor(const D3DXCOLOR & color)
{
	outline->SetColor(color);
}

/**************************************
Rect計算処理
***************************************/
RECT TextViewer::GetRect() const
{
	//テキストを中央寄せで表示するためのRectを計算
	LONG top = posY - fontSize / 2 * lineNum;
	LONG bottom = top + fontSize * lineNum;

	LONG left = posX;

	//NOTE:改行に対応してない
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
