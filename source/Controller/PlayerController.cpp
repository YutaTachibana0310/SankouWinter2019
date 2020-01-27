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
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Task/TaskManager.h"

#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"
#include "EnemyTimeController.h"
#include "../Camera/GameCamera.h"
#include "../Effect/GameParticleManager.h"
#include "../Actor/Player/PlayerColliderViewer.h"
#include "../Actor/Player/PowerupItemActor.h"

#include <algorithm>

/**************************************
�O���[�o���ϐ�
***************************************/
const float PlayerController::MaxEnergy = 100.0f;
const int PlayerController::MaxBomb = 3;
const int PlayerController::MaxLife = 2;

/**************************************
�R���X�g���N�^
***************************************/
PlayerController::PlayerController(GameCamera *camera) :
	camera(camera),
	cntEnergy(MaxEnergy),
	inSlow(false),
	cntLife(MaxLife),
	cntBomb(MaxBomb)
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	ResourceManager::Instance()->MakePolygon("PlayerCollider", "data/TEXTURE/Player/playerCollider.png", { 1.0f, 1.0f }, { 3.0f, 2.0f });
	ResourceManager::Instance()->MakePolygon("PowerupItem", "data/TEXTURE/Player/PowerupItem.png", { 3.0f, 3.0f });

	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	itemContainer.reserve(5);

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1, std::placeholders::_2);
	player->onFireBullet = onFireBullet;

	auto onHitPlayer = std::bind(&PlayerController::CollisionPlayer, this, std::placeholders::_1);
	player->onColliderHit = onHitPlayer;

	auto onSlowDownEnemyBullet = std::bind(&PlayerController::SlowDownEnemyBullet, this, std::placeholders::_1);
	player->onSlowdownEnemyBullet = onSlowDownEnemyBullet;

	player->Init();

	itemContainer.push_back(new PowerupItemActor());
	itemContainer[0]->SetPosition({ 0.0f, 0.0f, 30.0f });
	itemContainer[0]->Init();
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerController::~PlayerController()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bulletController);

	Utility::DeleteContainer(itemContainer);
}

/**************************************
�X�V����
***************************************/
void PlayerController::Update()
{
	player->Update();

	bulletController->Update();

	for (auto&& item : itemContainer)
	{
		item->Update();
	}

	auto itr = std::remove_if(itemContainer.begin(), itemContainer.end(), [](auto item)
	{
		return !item->IsActive();
	});
	itemContainer.erase(itr, itemContainer.end());
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

	for (auto&& item : itemContainer)
	{
		item->Draw();
	}
}

/**************************************
�����蔻��`�揈��
***************************************/
void PlayerController::DrawCollider()
{
	player->DrawCollider();
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
�X���E�_�E�������ǂ���
***************************************/
bool PlayerController::InSlowdown() const
{
	return inSlow;
}

/**************************************
�v���C���[�̍��W�擾
***************************************/
D3DXVECTOR3 PlayerController::GetPlayerPosition() const
{
	return player->GetPosition();
}

/**************************************
�o���b�g���~�߂���͂̏���
***************************************/
void PlayerController::SlowDownEnemyBullet(bool isSlow)
{
	if (cntEnergy > 0.0f && isSlow)
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
�v���C���[�̓����蔻��
***************************************/
void PlayerController::CollisionPlayer(ColliderObserver * other)
{
	std::string otherTag = other->Tag();
	if (otherTag == "Enemy")
	{
		GameParticleManager::Instance()->Generate(GameEffect::PlayerExplosion, player->GetPosition());

		auto callback = std::bind(&PlayerController::OnFinishCameraFocus, this);
		bool res = camera->Focus(player->GetPosition(), callback);

		if (!res)
		{
			OnFinishCameraFocus();
		}
	}
	else if (otherTag == "Item")
	{
		Debug::Log("Hit Item");
	}
}

/**************************************
�J�����t�H�[�J�X�I�����̃R�[���o�b�N
***************************************/
void PlayerController::OnFinishCameraFocus()
{
	player->Uninit();

	if (cntLife > 0)
	{
		cntLife--;
		TaskManager::Instance()->CreateDelayedTask(120.0f, true, [this]()
		{
			player->Init();
		});
	}
}
