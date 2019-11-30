//=====================================
//
//PlayerBulletController.cpp
//�@�\:�v���C���[�o���b�g�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Core/ObjectPool.h"

#include "../Actor/Player/PlayerBulletActor.h"

#include <algorithm>
#include <functional>

/**************************************
�R���X�g���N�^
***************************************/
PlayerBulletController::PlayerBulletController()
{
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerBulletController::~PlayerBulletController()
{
	Utility::DeleteContainer(bulletContainer);
}

/**************************************
�X�V����
***************************************/
void PlayerBulletController::Update()
{
	for (auto&& bullet : bulletContainer)
	{
		bullet->Update();
	}

	for (auto&& bullet : bulletContainer)
	{
		if (bullet->IsActive())
			continue;

		bullet->Uninit();
		ObjectPool::Instance()->Destroy(bullet);
		bullet = nullptr;
	}

	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto bullet) {return bullet == nullptr; });
	bulletContainer.erase(itr, bulletContainer.end());
}

/**************************************
�`�揈��
***************************************/
void PlayerBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	std::sort(bulletContainer.begin(), bulletContainer.end(), std::greater<>());
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
���ˏ���
***************************************/
void PlayerBulletController::FireBullet(const D3DXVECTOR3 & pos)
{
	PlayerBulletActor* bullet = ObjectPool::Instance()->Create<PlayerBulletActor>();
	bullet->Init(pos);
	bulletContainer.push_back(bullet);
}
