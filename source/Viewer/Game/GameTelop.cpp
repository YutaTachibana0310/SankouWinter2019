//=====================================
//
//GameTelop.cpp
//機能:ゲーム中テロップ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameTelop.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Task/TaskManager.h"

/**************************************
グローバル変数
***************************************/
static const char* TelopTexture[] =
{
	"data/TEXTURE/Viewer/GameStart.png",
	"data/TEXTURE/Viewer/StageClear.png",
	"data/TEXTURE/Viewer/GameOver.png",
};

static const D3DXVECTOR2 SizeTelop[] =
{
	{ 800.0f, 200.0f },
	{ 800.0f, 200.0f },
	{ 800.0f, 200.0f },
};

/**************************************
コンストラクタ
***************************************/
GameTelop::GameTelop() :
	callback(nullptr)
{
	polygon = std::make_shared<Polygon2D>();
	polygon->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	polygon->SetActive(false);

	for (int i = 0; i < TypeMax; i++)
	{
		ResourceManager::Instance()->LoadTexture(TelopTexture[i]);
	}
}

/**************************************
デストラクタ
***************************************/
GameTelop::~GameTelop()
{
	polygon.reset();
}

/**************************************
描画処理
***************************************/
void GameTelop::Draw()
{
	if (!polygon->IsActive())
		return;

	polygon->Draw();
}

/**************************************
再生処理
***************************************/
void GameTelop::Play(TelopType type, const std::function<void()>& callback)
{
	this->callback = callback;

	polygon->LoadTexture(TelopTexture[type]);
	polygon->SetSize(SizeTelop[type]);

	polygon->SetActive(true);

	auto onFinishTelopin = std::bind(&GameTelop::OnFinishTelopIn, this);
	Tween::Expand(polygon, ExpandType::ToLeftRight, 60.0f, EaseType::InOutCubic, true, onFinishTelopin);
}

/**************************************
テロップイン終了コールバック
***************************************/
void GameTelop::OnFinishTelopIn()
{
	auto onFinishTelopOut = std::bind(&GameTelop::OnFinishTelopOut, this);
	TaskManager::Instance()->CreateDelayedTask(120.0f, true, [=]()
	{
		Tween::Close(polygon, CloseType::FromLeftRight, 60.0f, EaseType::InOutCubic, true, onFinishTelopOut);
	});
}

/**************************************
テロップアウト終了コールバック
***************************************/
void GameTelop::OnFinishTelopOut()
{
	polygon->SetActive(false);

	if (callback != nullptr)
		callback();
}
