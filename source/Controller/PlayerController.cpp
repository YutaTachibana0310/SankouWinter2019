//=====================================
//
//PlayerController.cpp
//�@�\:�v���C���[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Input/input.h"

#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"
#include "EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const float PlayerController::MaxEnergy = 100.0f;
const int PlayerController::MaxBomb = 3;
const int PlayerController::MaxLife = 2;

/**************************************
�R���X�g���N�^
***************************************/
PlayerController::PlayerController() :
	cntEnergy(MaxEnergy),
	cntLife(MaxLife),
	cntBomb(MaxBomb)
{
	ResourceManager::Instance()->MakePolygon("PlayerBullet", "data/TEXTURE/Player/BlazeBullet.png", { 2.0f, 1.0f });
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	
	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1);
	player->onFireBullet = onFireBullet;

	player->Init();
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerController::~PlayerController()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bulletController);
}

/**************************************
�X�V����
***************************************/
void PlayerController::Update()
{
	InputEnemyBulletSlowDown();

	player->Update();

	bulletController->Update();
}

/**************************************
�`�揈��
***************************************/
void PlayerController::Draw()
{
	player->Draw();
}

/**************************************
�o���b�g�`�揈��
***************************************/
void PlayerController::DrawBullet()
{
	bulletController->Draw();
}

/**************************************
�G�i�W�[�̎c�芄���擾����
***************************************/
float PlayerController::GetPercentEnergy() const
{
	return cntEnergy / MaxEnergy;
}

/**************************************
�c�@���擾����
***************************************/
int PlayerController::GetCntLife() const
{
	return cntLife;
}

/**************************************
�{���o�[�c���擾����
***************************************/
int PlayerController::GetCntBomb() const
{
	return cntBomb;
}

/**************************************
�o���b�g���~�߂���͂̏���
***************************************/
void PlayerController::InputEnemyBulletSlowDown()
{
	if (Keyboard::GetPress(DIK_X) && cntEnergy >= 0.0f)
	{
		cntEnergy -= Math::Clamp(0.0f, MaxEnergy, 0.2f * FixedTime::GetTimeScale());
		EnemyTimeController::SlowDownBullet(true);
	}
	else
	{
		EnemyTimeController::SlowDownBullet(false);
	}
}
