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
#include "../../Framework/Core/ObjectPool.h"

#include "../Actor/Player/PlayerActor.h"
#include "PlayerBulletController.h"
#include "EnemyTimeController.h"
#include "../Camera/GameCamera.h"
#include "../Effect/GameParticleManager.h"
#include "../Actor/Player/PlayerColliderViewer.h"
#include "../Actor/Player/PowerupItemActor.h"
#include "../Viewer/Back/BackViewer.h"
#include "../System/GameScore.h"

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
PlayerController::PlayerController(GameCamera *camera, BackViewer *backViewer) :
	camera(camera),
	backViewer(backViewer),
	cntEnergy(MaxEnergy),
	inSlow(false),
	cntLife(MaxLife),
	cntBomb(MaxBomb)
{
	ResourceManager::Instance()->LoadMesh("Player", "data/MODEL/Player/Player.x");
	ResourceManager::Instance()->LoadMesh("PlayerTurret", "data/MODEL/Player/PlayerTurret.x");
	ResourceManager::Instance()->MakePolygon("PlayerCollider", "data/TEXTURE/Player/playerCollider.png", { 1.0f, 1.0f }, { 3.0f, 2.0f });
	ResourceManager::Instance()->MakePolygon("PowerupItem", "data/TEXTURE/Player/PowerupItem.png", { 3.0f, 3.0f });
	ResourceManager::Instance()->MakePolygon("PlayerShield", "data/TEXTURE/Player/PlayerShield.png", { 7.0f, 4.5f });

	player = new PlayerActor();
	bulletController = new PlayerBulletController();

	itemContainer.reserve(5);

	auto onFireBullet = std::bind(&PlayerBulletController::FireBullet, bulletController, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	player->onFireBullet = onFireBullet;

	auto onHitPlayer = std::bind(&PlayerController::CollisionPlayer, this, std::placeholders::_1);
	player->onColliderHit = onHitPlayer;

	auto onSlowDownEnemyBullet = std::bind(&PlayerController::SlowDownEnemyBullet, this, std::placeholders::_1);
	player->onSlowdownEnemyBullet = onSlowDownEnemyBullet;

	auto onFireBomber = std::bind(&PlayerController::FireBomber, this);
	player->onFireBomber = onFireBomber;
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
�v���C���[������
***************************************/
void PlayerController::Init()
{
	player->Init();
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
�p���[�A�b�v�A�C�e����������
***************************************/
void PlayerController::SetPowerupItem(const D3DXVECTOR3 & position)
{
	PowerupItemActor *item = ObjectPool::Instance()->Create<PowerupItemActor>();
	item->SetPosition(position);
	item->Init();
	itemContainer.push_back(item);
}

/**************************************
�G�i�W�[���Z����
***************************************/
void PlayerController::AddEnergy(float energy)
{
	cntEnergy = Math::Clamp(0.0f, MaxEnergy, cntEnergy + energy);
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
	if (otherTag == "EnemyBullet" || otherTag == "Enemy")
	{
		if (!player->IsInvincivle())
		{
			GameParticleManager::Instance()->Generate(GameEffect::PlayerExplosion, player->GetPosition());
			GameScore::Instance()->ResetCombo();

			auto callback = std::bind(&PlayerController::OnFinishCameraFocus, this);
			bool res = camera->Focus(player->GetPosition(), callback);

			if (!res)
			{
				OnFinishCameraFocus();
			}
		}
	}
	else if (otherTag == "Item")
	{
		player->PowerUp();
		backViewer->PlayPowerUp();
	}
}

/**************************************
�J�����t�H�[�J�X�I�����̃R�[���o�b�N
***************************************/
void PlayerController::OnFinishCameraFocus()
{
	if (cntLife > 0)
	{
		cntLife--;

		const D3DXVECTOR3 playerrPosition = player->GetPosition();
		int level = Math::Clamp(1, 3, player->PowerLevel());
		for (int i = 0; i < level; i++)
		{
			SetPowerupItem(playerrPosition);
		}

		TaskManager::Instance()->CreateDelayedTask(120.0f, true, [this]()
		{
			player->Init();
		});
	}

	player->Uninit();
}

/**************************************
�{���o�[����
***************************************/
void PlayerController::FireBomber()
{
	if (cntBomb <= 0)
		return;

	--cntBomb;

	D3DXVECTOR3 playerPos = player->GetPosition();
	
	playerPos.z = Math::Clamp(-50.0f, 50.0f, playerPos.z + 40.0f);

	GameParticleManager::Instance()->GenerareBomber(playerPos);

}
