//=====================================
//
//TutorialPlayerController.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialPlayerController.h"
#include "../Actor/Player/PlayerActor.h"
#include "EnemyTimeController.h"
#include "PlayerBulletController.h"

#include <functional>

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
***************************************/
TutorialPlayerController::~TutorialPlayerController()
{
}

/**************************************
�V���b�g�ېݒ�
***************************************/
void TutorialPlayerController::EnableShot(bool state)
{
	enableShot = state;
}

/**************************************
�X���E�_�E���ېݒ�
***************************************/
void TutorialPlayerController::EnableSlowdown(bool state)
{
	enableSlowdown = state;
}

/**************************************
�{���o�[�ېݒ�
***************************************/
void TutorialPlayerController::EnableBomber(bool state)
{
	enableBomber = state;
}

/**************************************
�G�e����
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
�{���o�[����
***************************************/
void TutorialPlayerController::FireBomber()
{
	if (!enableBomber)
		return;

	PlayerController::FireBomber();
}

/**************************************
�o���b�g����
***************************************/
void TutorialPlayerController::FireBullet(const D3DXVECTOR3 & pos, bool isMain, int level)
{
	if (!enableShot)
		return;

	bulletController->FireBullet(pos, isMain, level);
}
