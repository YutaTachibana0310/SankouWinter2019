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

#include "../../Library/nameof/nameof.hpp"

#include "../Actor/Enemy/EnemyBulletActor.h"

#include <algorithm>

#include "../Handler/EnemyBulletHandler.h"

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
		EnemyBulletConfig::SizePolygon,
		EnemyBulletConfig::SplitTexture);
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
	});

	//�폜�����o���b�g���R���e�i���珜�O
	auto itr = std::remove_if(bulletContainer.begin(), bulletContainer.end(), [](auto ptr)
	{
		return !ptr->IsActive();
	});
	bulletContainer.erase(itr, bulletContainer.end());

	//�f�o�b�O���j���[
	Debug::Begin("EnemyBullet");
	static int bulletType = EnemyBulletConfig::Type(0);

	if (Debug::Button("Shot"))
	{
		Transform transform;
		SetBullet(transform,  EnemyBulletConfig::Type(bulletType), 0.5f);
	}

	if (Debug::Button("Way Shot"))
	{
		Transform transform;
		EnemyBulletHandler handle(this);

		handle.SetWayBullet(transform, EnemyBulletConfig::Type(bulletType), 0.5f, 5, 60);
	}

	if (Debug::Button("Circle Shot"))
	{
		Transform transform;
		EnemyBulletHandler handle(this);

		handle.SetCircleBullet(transform, EnemyBulletConfig::Type(bulletType), 0.5f, 16);
	}

	if (Debug::Button("Strew Shot"))
	{
		Transform transform;
		EnemyBulletHandler handle(this);

		handle.SetStrewBullet(transform, EnemyBulletConfig::Type(bulletType), 0.5f, 30.0f);
	}

	for (int i = 0; i < EnemyBulletConfig::Type::EnemyBulletMax; i++)
	{
		std::string label = std::string(NAMEOF_ENUM(EnemyBulletConfig::Type(i)));
		Debug::RadioButton(label.c_str(), bulletType, i);
	}

	Debug::End();
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	for (auto&& bullet : bulletContainer)
	{
		bullet->DrawBloom();
	}

	for (auto&& bullet : bulletContainer)
	{
		bullet->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**************************************
�o���b�g�Z�b�g����
***************************************/
void EnemyBulletController::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	if (cntBullet > MaxBullet)
	{
		Debug::Log("EnemyBullet is Max");
		return;
	}

	EnemyBulletActor* bullet = ObjectPool::Instance()->Create<EnemyBulletActor>();
	bullet->Init(shotTransform);

	bullet->SetType(type);
	bullet->SetSpeed(speed);

	bulletContainer.push_back(bullet);
}
