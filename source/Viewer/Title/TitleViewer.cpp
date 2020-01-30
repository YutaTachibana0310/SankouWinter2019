//=====================================
//
//TitleViewer.cpp
//機能:タイトルビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Tween/Tween.h"

#include "TitleGear.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TitleViewer::TitleViewer()
{
	titleLogo = new Polygon2D();
	titleLogo->LoadTexture("data/TEXTURE/Viewer/TitleLogo.png");
	titleLogo->SetSize({ 512.0f, 128.0f });
	titleLogo->SetPosition({ SCREEN_CENTER_X, 360.0f, 0.0f });

	centerGear = new TitleGear();
	centerGear->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });

	
	rightGear = new TitleGear();
	leftGear = new TitleGear();

	const float ScaleGear = 2.5f;
	rightGear->SetScale(Vector3::One * ScaleGear);
	leftGear->SetScale(Vector3::One * ScaleGear);

	const float OffsetGear = 1024.0f;
	rightGear->SetPosition({ (float)SCREEN_WIDTH + OffsetGear, (float)SCREEN_HEIGHT, 0.0f });
	leftGear->SetPosition({ -OffsetGear, 0.0f, 0.0f });

	const float DurationTween = 45.0f;
	Tween::Move(*rightGear, { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f }, DurationTween, EaseType::OutCubic, true);
	Tween::Move(*leftGear, { 0.0f, 0.0f, 0.0f }, DurationTween, EaseType::OutCubic, true);
}

/**************************************
デストラクタ
***************************************/
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(titleLogo);
	SAFE_DELETE(centerGear);
	SAFE_DELETE(rightGear);
	SAFE_DELETE(leftGear);
}

/**************************************
更新処理
***************************************/
void TitleViewer::Update()
{
	centerGear->Update();
	leftGear->Update();
	rightGear->Update();
}

/**************************************
描画処理
***************************************/
void TitleViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);

	rightGear->Draw();
	leftGear->Draw();

	centerGear->Draw();

	titleLogo->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}
