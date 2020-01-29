//=====================================
//
//EnemyTrail.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyTrail.h"
#include "../../../Framework/Math/Easing.h"
#include "../../Controller/EnemyTimeController.h"

namespace Effect::Game 
{
	/**************************************
	EnemyTrailController�R���X�g���N�^
	***************************************/
	EnemyTrailController::EnemyTrailController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 1.0f, 1.0f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/EnemyTrail.png");

		const unsigned MaxEmitter = 128;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnemyTrailEmitter();
		}
	}

	/**************************************
	EnemyTrail�R���X�g���N�^
	***************************************/
	EnemyTrail::EnemyTrail() :
		Particle3D(5.0f, 10.0f),
		initScale(Math::RandomRange(0.5f, 1.5f))
	{

	}

	/**************************************
	EnemyTrail����������
	***************************************/
	void EnemyTrail::Init()
	{
		cntFrame = 0.0f;
		active = true;

		moveDir = transform->Forward();
		moveDir.y *= Math::RandomRange(-2.0f, 2.0f);
		moveDir.z *= Math::RandomRange(0.05f, 1.0f);
		moveDir = Vector3::Normalize(moveDir);
	}

	/**************************************
	EnemyTrail�X�V����
	***************************************/
	void EnemyTrail::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);

		const float Speed = 0.3f;
		transform->Move(moveDir * EnemyTimeController::GetTimeScale() * Speed);
	}

	/**************************************
	EnemyTrailEmitter�R���X�g���N�^
	***************************************/
	EnemyTrailEmitter::EnemyTrailEmitter() :
		Enemy::EnemyParticleEmitter(10)
	{
		Loop(true);

		const unsigned MaxParticle = 64;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemyTrail();
			AddChild(dynamic_cast<Particle3D*>(particle));
		}
	}
}