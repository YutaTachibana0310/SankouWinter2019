//=====================================
//
//EnergyEffect.cpp
//�@�\:�G�i�W�[�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnergyEffect.h"

namespace Effect::Game 
{
	/**************************************
	static�����o
	***************************************/
	const float EnergyEffect::LifeFrame = 60.0f;

	/**************************************
	EnergyEffectController�R���X�g���N�^
	***************************************/
	EnergyEffectController::EnergyEffectController() :
		BaseParticleController(Particle_2D)
	{
		const D3DXVECTOR2 Size = { 21.5f, -21.5f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/PlayerTrail.png");

		const unsigned MaxEmitter = 128;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnergyEffectEmitter();
		}
	}

	/**************************************
	EnergyEffectController�G�~�b�^�[�Z�b�g����
	***************************************/
	void EnergyEffectController::SetEmitter(const D3DXVECTOR3 & position, float energy)
	{
		auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
		{
			return !emitter->IsActive();
		});

		if (emitter == emitterContainer.end())
			return;

		auto ptr = dynamic_cast<EnergyEffectEmitter*>(*emitter);
		ptr->SetPosition(position);
		ptr->Init(nullptr);
		ptr->SetEnergy(energy);

		return;
	}

	/**************************************
	EnergyEffect�R���X�g���N�^
	***************************************/
	EnergyEffect::EnergyEffect() :
		Particle2D(LifeFrame),
		velocity(Vector3::Zero)
	{

	}

	/**************************************
	EnergyEffect����������
	***************************************/
	void EnergyEffect::Init()
	{
		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	EnergyEffect�X�V����
	***************************************/
	void EnergyEffect::Update()
	{
		if (!IsActive())
			return;

		D3DXVECTOR3 acceleration = Vector3::Zero;
		float t = 1.0f - cntFrame / lifeFrame;

		const D3DXVECTOR3 TargetPosition = { 900.0f, 80.0f, 0.0f };
		D3DXVECTOR3 diff = TargetPosition - transform->GetPosition();

		acceleration = (diff - velocity * t) * 2.0f / (t * t);

		cntFrame += FixedTime::GetTimeScale();

		velocity += acceleration / 60.0f * FixedTime::GetTimeScale();
		transform->Move(velocity / 60.0f * FixedTime::GetTimeScale());
	}

	/**************************************
	�����ݒ菈��
	***************************************/
	void EnergyEffect::SetDirection(const D3DXVECTOR3 & direction)
	{
		velocity = direction * 1500.0f;
	}

	/**************************************
	�G�i�W�[�ʐݒ菈��
	***************************************/
	void EnergyEffect::SetEnergy(float energy)
	{
		this->energy = energy;
	}

	/**************************************
	EnergyEffectEmitter�R���X�g���N�^
	***************************************/
	EnergyEffectEmitter::EnergyEffectEmitter() :
		BaseEmitter(8, 2.0f)
	{
		particleContainer.resize(8, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnergyEffect();
		}
	}

	/**************************************
	EnergyEffectEmitter���o����
	***************************************/
	bool EnergyEffectEmitter::Emit()
	{
		if (!enableEmit)
			return true;

		if (cntFrame < prevEmitTime)
			return true;

		prevEmitTime = ceilf(cntFrame);

		D3DXVECTOR3 direction = Vector3::Up;
		D3DXMATRIX mtxRot;
		D3DXMatrixRotationAxis(&mtxRot, &Vector3::Forward, D3DXToRadian(360.0f / 8.0f));

		for (auto&& particle : particleContainer)
		{
			if (particle->IsActive())
				continue;

			particle->SetTransform(*transform);
			particle->Init();

			EnergyEffect *effect = dynamic_cast<EnergyEffect*>(particle);
			effect->SetDirection(direction);
			effect->SetEnergy(energy / 8.0f);

			D3DXVec3TransformCoord(&direction, &direction, &mtxRot);
		}

		return true;
	}

	/**************************************
	�G�i�W�[�ʐݒ菈��
	***************************************/
	void EnergyEffectEmitter::SetEnergy(float energy)
	{
		this->energy = energy;
	}
}