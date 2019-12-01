//=====================================
//
//EnemyExplosion.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyExplosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	static�����o
	***************************************/
	const float EnemyExplosion::MaxSpeed = 1.2f;
	const float EnemyExplosion::MinSpeed = 0.2f;

	/**************************************
	EnemtExplosionController�R���X�g���N�^
	***************************************/
	EnemyExplosionController::EnemyExplosionController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 10.0f, 10.0f };
		const D3DXVECTOR2 TexDiv = { 4.0f, 4.0f };
		MakeUnitBuffer(Size, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/EnemyExplosion.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemyExplosion();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 64;
		const int NumEmit = 5;
		const int DurationEmit = 5;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	EnemyExplosion�R���X�g���N�^
	***************************************/
	EnemyExplosion::EnemyExplosion() :
		AnimationParticle3D(4.0f, 4.0f, 30, 60)
	{
		moveDir = Vector3::Random();
	}

	/**************************************
	EnemyExplosion����������
	***************************************/
	void EnemyExplosion::Init()
	{
		cntFrame = 0;
		active = true;

		initSpeed = Math::RandomRange(MinSpeed, MaxSpeed);

		D3DXVECTOR3 dir = { moveDir.z, moveDir.y, 0.0f };
		float angle = Vector3::Angle({ 1.0f, 1.0f, 0.0f }, dir);
		D3DXVECTOR3 axis = Vector3::Axis({ 1.0f, 1.0f, 0.0f }, dir);
		transform->Rotate(angle, axis);
	}

	/**************************************
	EnemyExplosion�X�V����
	***************************************/
	void EnemyExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, initSpeed, 0.0f, EaseType::OutSine);
		transform->Move(speed * moveDir);

		Animation(t);
	}
}