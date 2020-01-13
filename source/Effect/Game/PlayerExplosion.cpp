//=====================================
//
// PlayerExplosion.cpp
// �@�\:�v���C���[�����G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerExplosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	�O���[�o���ϐ�
	***************************************/

	/**************************************
	PlayerExplosionController�R���X�g���N�^
	***************************************/
	PlayerExplosionController::PlayerExplosionController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 2.0f, 2.0f };
		const D3DXVECTOR2 Split = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, Split);

		LoadTexture("data/TEXTURE/Particle/PlayerExplosion.png");

		const unsigned MaxParticle = 256;
		const unsigned MaxEmitter = 1;
		const float EmitDuration = 5;
		const int EmitNum = 64;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(EmitNum, EmitDuration);
			emitter->CreateParticleContainer<PlayerExplosion>(MaxParticle);
		}
	}

	/**************************************
	PlayerExplosion�R���X�g���N�^
	***************************************/
	PlayerExplosion::PlayerExplosion() :
		AnimationParticle3D(2.0f, 2.0f, 60.0f, 120.0f),
		moveDir(Vector3::Random()),
		speed(Math::RandomRange(0.15f, 2.2f)),
		initScale(Math::RandomRange(0.05f, 1.2f))
	{
		moveDir = Vector3::Normalize(moveDir);
	}

	/**************************************
	PlayerExplosion����������
	***************************************/
	void PlayerExplosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	PlayerExplosion�X�V����
	***************************************/
	void PlayerExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		float t = cntFrame / lifeFrame;

		float currentSpeed = Easing::EaseValue(t, speed, 0.0f, EaseType::OutCubic);
		transform->Move(moveDir * currentSpeed * FixedTime::GetTimeScale());

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);

		Animation(t * 15.0f);
	}
}