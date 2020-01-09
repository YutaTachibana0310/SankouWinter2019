//=====================================
//
//ポリゴン2Dヘッダ[Polygon2D.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Polygon2D : public GameObject
{
public:
	Polygon2D();
	virtual ~Polygon2D();

	virtual void Draw();

	virtual void SetSize(const D3DXVECTOR2& size);
	virtual void SetColor(D3DXCOLOR color);
	virtual void SetUV(float left, float top, float width, float height);

	virtual void LoadTexture(const char* path);

protected:
	VERTEX_2D vtxWk[NUM_VERTEX];
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR3 vtxPos[NUM_VERTEX];
	D3DXVECTOR2 vtxSize;
	D3DXVECTOR2 vtxUV[NUM_VERTEX];

	void SetVertex();

	friend class ViewerTweener;
};

#endif