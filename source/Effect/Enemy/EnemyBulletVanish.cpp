//=====================================
//
//EnemyBulletVanish.cpp
//�@�\:�G�l�~�[�o���b�g�����G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletVanish.h"
#include "../../../Framework/Math/Easing.h"
#include "../../Controller/EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/

namespace Effect::Game
{
	/**************************************
	EnemyBulletVanishController�R���X�g���N�^
	***************************************/
	EnemyBulletVanishController::EnemyBulletVanishController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 0.5f, 0.5f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/EnemyBulletVanish.png");

		const unsigned MaxEmitter = 2048;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnemyBulletVanishEmitter();
		}
	}

	/**************************************
	EnemyBulletVanish�R���X�g���N�^
	***************************************/
	EnemyBulletVanish::EnemyBulletVanish() :
		Particle3D(20.0f, 40.0f),
		moveDir(Vector3::Random()),
		speed(Math::RandomRange(0.05f, 1.0f)),
		initScale(Math::RandomRange(0.6f, 1.5f))
	{

	}

	/**************************************
	EnemyBulletVanish����������
	***************************************/
	void EnemyBulletVanish::Init()
	{
		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	EnemyBulletVanish�X�V����
	***************************************/
	void EnemyBulletVanish::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);

		transform->Move(moveDir * speed * EnemyTimeController::GetTimeScale());
	}

	/**************************************
	EnemyBulletVanishEmitter�R���X�g���N�^
	***************************************/
	EnemyBulletVanishEmitter::EnemyBulletVanishEmitter() :
		Enemy::EnemyParticleEmitter(16, 3.0f)
	{
		particleContainer.resize(16, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemyBulletVanish();
		}
	}
}