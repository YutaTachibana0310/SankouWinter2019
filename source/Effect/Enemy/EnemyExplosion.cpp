//=====================================
//
//EnemyExplosion.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyExplosion.h"
#include "../../../Framework/Math/Easing.h"
#include "../../Controller/EnemyTimeController.h"
#include "../Enemy/EnemyParticleEmitter.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float EnemyExplosion::MaxSpeed = 1.2f;
	const float EnemyExplosion::MinSpeed = 0.2f;

	/**************************************
	EnemtExplosionControllerコンストラクタ
	***************************************/
	EnemyExplosionController::EnemyExplosionController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 10.0f, 10.0f };
		const D3DXVECTOR2 TexDiv = { 4.0f, 4.0f };
		MakeUnitBuffer(Size, TexDiv);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/EnemyExplosion.png");

		//エミッタコンテナ作成
		const unsigned MaxParticle = 32;
		const unsigned MaxEmitter = 16;
		const int NumEmit = 5;
		const float DurationEmit = 5.0f;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new Enemy::EnemyParticleEmitter(NumEmit, DurationEmit);
			emitter->CreateParticleContainer<EnemyExplosion>(MaxParticle);
		}
	}

	/**************************************
	EnemyExplosionコンストラクタ
	***************************************/
	EnemyExplosion::EnemyExplosion() :
		AnimationParticle3D(4.0f, 4.0f, 30, 60)
	{
		moveDir = Vector3::Random();
	}

	/**************************************
	EnemyExplosion初期化処理
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
	EnemyExplosion更新処理
	***************************************/
	void EnemyExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, initSpeed, 0.0f, EaseType::OutSine);
		transform->Move(speed * moveDir * EnemyTimeController::GetTimeScale());

		Animation(t);
	}
}
