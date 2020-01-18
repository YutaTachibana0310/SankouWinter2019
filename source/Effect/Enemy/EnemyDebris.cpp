//=====================================
//
// EnemyDebris.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyDebris.h"
#include "../../../Framework/Math/Easing.h"
#include "EnemyParticleEmitter.h"
#include "../../Controller/EnemyTimeController.h"

namespace Effect::Game
{
	/**************************************
	グローバル変数
	***************************************/

	/**************************************
	EnemyDebrisControllerコンストラクタ
	***************************************/
	EnemyDebrisController::EnemyDebrisController() :
		BaseParticleController(Particle_3D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 0.75f, 0.75f };
		MakeUnitBuffer(Size);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/EnemyDebris.png");

		//エミッタコンテナ作成
		const unsigned MaxParticle = 256;
		const unsigned MaxEmitter = 16;
		const float DurationEmit = 3;
		const int NumEmit = 128;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnemyDebrisEmitter();
		}
	}

	/**************************************
	EnemyDebrisコンストラクタ
	***************************************/
	EnemyDebris::EnemyDebris() :
		Particle3D(20.0f, 30.0f),
		moveDir(Vector3::Random()),
		speed(Math::RandomRange(0.05f, 1.0f))
	{

	}

	/**************************************
	EnemyDebris初期化処理
	***************************************/
	void EnemyDebris::Init()
	{
		active = true;
		cntFrame = 0.0f;

		transform->Move(moveDir * Math::RandomRange(0.0f, 3.0f));
	}

	/**************************************
	EnemyDebris更新処理
	***************************************/
	void EnemyDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);

		transform->Move(EnemyTimeController::GetTimeScale() * moveDir * speed);
	}

	/**************************************
	EnemyDebrisEmitterコンストラクタ
	***************************************/
	EnemyDebrisEmitter::EnemyDebrisEmitter() :
		EnemyParticleEmitter(128, 3.0f)
	{
		particleContainer.resize(256);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemyDebris();
		}
	}
}
