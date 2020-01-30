//=====================================
//
//TitleGear.cpp
//機能:タイトル歯車
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleGear.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TitleGear::TitleGear()
{
	innerGear = new Polygon2D();
	outerGear = new Polygon2D();

	AddChild(innerGear);
	AddChild(outerGear);

	innerGear->LoadTexture("data/TEXTURE/Viewer/InnerGear.png");
	outerGear->LoadTexture("data/TEXTURE/Viewer/OuterGear.png");

	innerGear->SetSize({ 256.0f, 256.0f });
	outerGear->SetSize({ 256.0f, 256.0f });
}

/**************************************
デストラクタ
***************************************/
TitleGear::~TitleGear()
{
	SAFE_DELETE(innerGear);
	SAFE_DELETE(outerGear);
}

/**************************************
更新処理
***************************************/
void TitleGear::Update()
{
	D3DXVECTOR3 rotation = innerGear->GetRotation();
	rotation.z += 0.2f;
	innerGear->SetRotatition(rotation);

	rotation = outerGear->GetRotation();
	rotation.z -= 0.2f;
	outerGear->SetRotatition(rotation);
}

/**************************************
描画処理
***************************************/
void TitleGear::Draw()
{
	innerGear->Draw();
	outerGear->Draw();
}
