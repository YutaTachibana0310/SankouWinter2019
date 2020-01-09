//=====================================
//
//PlayerBulletHit.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletHit.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	PlayerBulletHitControllerコンストラクタ
	***************************************/
	PlayerBulletHitController::PlayerBulletHitController() :
		BaseParticleController(Particle_3D)
	{
		//テクスチャ読み込み
		const char* TextureName = "data/TEXTURE/Particle/PlayerBulletHit.png";
		LoadTexture(TextureName);

		//単位頂点バッファ作成
		const D3DXVECTOR2 Size = { 0.5f, 0.5f };
		MakeUnitBuffer(Size);

		//エミッタコンテナ作成
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
	PlayerBulletHitコンストラクタ
	***************************************/
	PlayerBulletHit::PlayerBulletHit() :
		Particle3D(10, 20)
	{
		moveDir = { Math::RandomRange(-0.2f, 0.2f), Math::RandomRange(-0.5f, 0.5f), -1.0f };
		moveDir = Vector3::Normalize(moveDir);

		initScale = Math::RandomRange(0.3f, 1.2f);
	}

	/**************************************
	PlayerBulletHit初期化処理
	***************************************/
	void PlayerBulletHit::Init()
	{
		active = true;
		cntFrame = 0;
	}

	/**************************************
	PlayerBulletHit更新処理
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
