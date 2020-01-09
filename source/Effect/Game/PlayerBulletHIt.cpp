//=====================================
//
//PlayerBulletHit.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletHit.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	PlayerBulletHitController�R���X�g���N�^
	***************************************/
	PlayerBulletHitController::PlayerBulletHitController() :
		BaseParticleController(Particle_3D)
	{
		//�e�N�X�`���ǂݍ���
		const char* TextureName = "data/TEXTURE/Particle/PlayerBulletHit.png";
		LoadTexture(TextureName);

		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 0.5f, 0.5f };
		MakeUnitBuffer(Size);

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxParticle = 16;
		const unsigned MaxEmitter = 32;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(5, 3);
			emitter->CreateParticleContainer<PlayerBulletHit>(MaxParticle);
		}
	}

	/**************************************
	PlayerBulletHit�R���X�g���N�^
	***************************************/
	PlayerBulletHit::PlayerBulletHit() :
		Particle3D(10, 20)
	{
		moveDir = { Math::RandomRange(-0.2f, 0.2f), Math::RandomRange(-0.5f, 0.5f), -1.0f };
		moveDir = Vector3::Normalize(moveDir);

		initScale = Math::RandomRange(0.3f, 1.2f);
	}

	/**************************************
	PlayerBulletHit����������
	***************************************/
	void PlayerBulletHit::Init()
	{
		active = true;
		cntFrame = 0;
	}

	/**************************************
	PlayerBulletHit�X�V����
	***************************************/
	void PlayerBulletHit::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);

		transform->Move(moveDir * 0.2f * FixedTime::GetTimeScale());
	}
}
