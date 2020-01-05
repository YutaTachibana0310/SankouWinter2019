//=====================================
//
// EnemyBulletController.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletController.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Core/ObjectPool.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../Actor/Enemy/EnemyBulletActor.h"

#include <algorithm>

/**************************************
�O���[�o���ϐ�
***************************************/
const unsigned EnemyBulletController::MaxBullet = 4096;

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletController::EnemyBulletController() :
	cntBullet(0)
{
	bulletContainer.reserve(4096);

	ResourceManager::Instance()->MakePolygon(
		"EnemyBullet",
		"data/TEXTURE/Enemy/EnemyBullet.png",
		{ 2.0f, 2.0f },
		{ 8.0f, 8.0f });
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletController::~EnemyBulletController()
{
	Utility::DeleteContainer(bulletContainer);
}

/**************************************
�X�V����
***************************************/
void EnemyBulletController::Update()
{
	//�X�V
	for (auto&& bullet : bulletContainer)
	{
		bullet->Update();
	}

	//��A�N�e�B�u�ɂȂ����o���b�g��ObjectPool�ֈړ�
	std::for_each(bulletContainer.begin(), bulletContainer.end(), [](auto bullet)
	{
		if (bullet->IsActive())
			return;

		ObjectPool::Instance()->Destroy<EnemyBulletActor>(bullet);
		bullet = nullptr;
	});

	//�폜�����o���b�g���R���e�i���珜�O
	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto ptr)
	{
		return ptr == nullptr;
	});
	bulletContainer.erase(itr, bulletContainer.end());
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletController::Draw()
{
	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}
}

/**************************************
�o���b�g�Z�b�g����
***************************************/
void EnemyBulletController::SetBullet(const Transform & shotTransform)
{
	if (cntBullet > MaxBullet)
	{
		Debug::Log("EnemyBullet is Max");
		return;
	}

	EnemyBulletActor* bullet = ObjectPool::Instance()->Create<EnemyBulletActor>();
	bullet->Init(shotTransform);

	bulletContainer.push_back(bullet);
}
