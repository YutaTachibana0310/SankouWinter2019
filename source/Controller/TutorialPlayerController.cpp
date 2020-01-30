//=====================================
//
//TutorialPlayerController.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialPlayerController.h"
#include "../Actor/Player/PlayerActor.h"
#include "EnemyTimeController.h"
#include "PlayerBulletController.h"

#include <functional>

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TutorialPlayerController::TutorialPlayerController(GameCamera * camera, BackViewer * backViewer) :
	PlayerController(camera, backViewer),
	enableShot(false),
	enableSlowdown(false),
	enableBomber(false)
{
	using namespace std::placeholders;

	auto onFireShot = std::bind(&TutorialPlayerController::FireBullet, this, _1, _2, _3);
	player->onFireBullet = onFireShot;

	auto onSlowDown = std::bind(&TutorialPlayerController::SlowDownEnemyBullet, this, _1);
	player->onSlowdownEnemyBullet = onSlowDown;

	auto onFireBomber = std::bind(&TutorialPlayerController::FireBomber, this);
	player->onFireBomber = onFireBomber;
}

/**************************************
デストラクタ
***************************************/
TutorialPlayerController::~TutorialPlayerController()
{
}

/**************************************
ショット可否設定
***************************************/
void TutorialPlayerController::EnableShot(bool state)
{
	enableShot = state;
}

/**************************************
スロウダウン可否設定
***************************************/
void TutorialPlayerController::EnableSlowdown(bool state)
{
	enableSlowdown = state;
}

/**************************************
ボンバー可否設定
***************************************/
void TutorialPlayerController::EnableBomber(bool state)
{
	enableBomber = state;
}

/**************************************
敵弾減速
***************************************/
void TutorialPlayerController::SlowDownEnemyBullet(bool isSlow)
{
	if (cntEnergy > 0.0f && isSlow && enableSlowdown)
	{
		cntEnergy -= Math::Clamp(0.0f, MaxEnergy, 0.2f * FixedTime::GetTimeScale());
		EnemyTimeController::SlowDownBullet(true);
		inSlow = true;
	}
	else
	{
		EnemyTimeController::SlowDownBullet(false);
		inSlow = false;
	}
}

/**************************************
ボンバー発射
***************************************/
void TutorialPlayerController::FireBomber()
{
	if (!enableBomber)
		return;

	PlayerController::FireBomber();
}

/**************************************
バレット発射
***************************************/
void TutorialPlayerController::FireBullet(const D3DXVECTOR3 & pos, bool isMain, int level)
{
	if (!enableShot)
		return;

	bulletController->FireBullet(pos, isMain, level);
}
