//=====================================
//
//PlayerTrail.cpp
//�@�\:�v���C���[�g���C���G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerTrail.h"

namespace Effect::Game
{
	/**************************************
	PlayerTrailController�R���X�g���N�^
	***************************************/
	PlayerTrailController::PlayerTrailController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 1.0f, 1.0f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/PlayerTrail.png");

		const unsigned MaxEmitter = 9;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new PlayerTrailEmitter();
		}
	}

	/**************************************
	PlayerTrail�R���X�g���N�^
	***************************************/
	PlayerTrail::PlayerTrail() :
		Particle3D(3.0f, 15.0f),
		initScale(Math::RandomRange(0.3f, 1.0f))
	{

	}

	/**************************************
	PlayerTrail����������
	***************************************/
	void PlayerTrail::Init()
	{
		const D3DXVECTOR3 Offset = Vector3::Random();
		const float LengthOffset = Math::RandomRange(0.0f, 1.5f);
		transform->Move(Offset * LengthOffset);

		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	PlayerTrail�X�V����
	***************************************/
	void PlayerTrail::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		const float Speed = 0.8f;
		transform->Move(Vector3::Back * Speed * FixedTime::GetTimeScale());
	}

	/**************************************
	PlayerTrailEmitter�R���X�g���N�^
	***************************************/
	PlayerTrailEmitter::PlayerTrailEmitter() :
		BaseEmitter(10)
	{
		const unsigned MaxParticle = 64;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new PlayerTrail();
			AddChild(dynamic_cast<PlayerTrail*>(particle));
		}

		Loop(true);
	}
}