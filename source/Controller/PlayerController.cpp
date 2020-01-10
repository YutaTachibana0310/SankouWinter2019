//=====================================
//
//PlayerController.cpp
//�@�\:�v���C���[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PlayerController::PlayerController()
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
