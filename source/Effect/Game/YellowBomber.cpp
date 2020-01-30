//=====================================
//
//YellowBomber.cpp
//機能:イエローボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "YellowBomber.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	YellowBomberControllerコンストラクタ
	***************************************/
	YellowBomberController::YellowBomberController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 15.0f, 15.0f };
		const D3DXVECTOR2 Split = { 4.0f, 2.0f };
		MakeUnitBuffer(Size, Split);

		LoadTexture("data/TEXTURE/Particle/YellowExplosion.png");

		const unsigned MaxEmitter = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(5, 240.0f);
			emitter->CreateParticleContainer<YellowBomber>(256);
		}
	}

	/**************************************
	YellowBomberコンストラクタ
	***************************************/
	YellowBomber::YellowBomber() :
		AnimationParticle3D(4.0f, 2.0f, 30.0f, 60.0f)
	{

	}

	/**************************************
	YellowBomber初期化処理
	***************************************/
	void YellowBomber::Init()
	{
		cntFrame = 0.0f;
		active = true;

		const D3DXVECTOR3 Offset = Vector3::Random() * Math::RandomRange(0.0f, 15.0f);
		transform->Move(Offset);

		transform->SetScale(Vector3::Zero);

		scale = Math::RandomRange(0.5f, 1.2f);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);
	}

	/**************************************
	YellowBomber更新処理
	***************************************/
	void YellowBomber::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		float t = cntFrame / lifeFrame;
		if (t / 0.2f <= 1.0f)
		{
			float currentScale = Easing::EaseValue(t / 0.2f, 0.0f, scale, EaseType::OutCubic);
			transform->SetScale(Vector3::One * currentScale);
		}
		else if (t >= 0.8f)
		{
			t -= 0.8f;
			t *= 5.0f;
			float currentScale = Easing::EaseValue(t, scale, 0.0f, EaseType::OutCubic);
			transform->SetScale(Vector3::One * currentScale);
		}

		transform->Rotate(0.2f, Vector3::Forward);
	}

}