//=====================================
//
//TextViewer.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_

#include "../../main.h"

#include <string>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TextViewer : public GameObject
{
public:
	
	//水平方向のレイアウト
	enum class HorizontalAlignment
	{
		Left = 0x00,		//左寄せ
		Center = 0x01,		//中央寄せ
		Right = 0x02		//右寄せ
	};

	//垂直方向のレイアウト
	enum class VerticalAlignment
	{
		Top = 0x00,			//上寄せ
		Center = 0x04,		//中央寄せ
		Bottom = 0x08		//下寄せ
	};
	
	//コンストラクタ
	//fontName : 使用するフォントの名前 ※フォントファイルへのパスではないので注意
	//size : 表示フォントサイズ
	TextViewer(const char* fontName, int size);

	//デストラクタ
	virtual ~TextViewer();

	//描画処理
	virtual void Draw(void);

	//カラーセット処理
	virtual void SetColor(const D3DXCOLOR& color);

	//表示テキストセット処理
	virtual void SetText(const std::string& message);

	//表示テキスト取得処理
	std::string GetText() const;

	//イタリック使用設定
	void UseItalic(bool state);

	//アウトライン使用設定
	void UseOutLine(bool state);

	//水平方向のレイアウト設定
	void SetHorizontalAlignment(HorizontalAlignment alignment);

	//垂直方向のレイアウト設定
	void SetVerticalAlignment(VerticalAlignment alignment);

	//アウトラインの幅設定
	void SetOutlineWidth(int width);

	//アウトラインのカラー設定
	void SetOutlineColor(const D3DXCOLOR& color);

private:
	//フォントインターフェイス
	LPD3DXFONT font;
	LPD3DXFONT italicFont;

	//フォントサイズ
	int fontSize;

	//表示座標
	int posX;
	int posY;

	//行数
	int lineNum;

	//表示カラー
	D3DXCOLOR color;

	//イタリック使用
	bool useItalic;

	//アウトライン使用
	bool useOutline;

	//レイアウト
	HorizontalAlignment horizontal;
	VerticalAlignment vertical;

	//表示文字列
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif

	//Rect計算処理
	RECT GetRect() const;

	//アウトライン用内部クラス
	class OutLine;
	OutLine* outline;
};

#endif