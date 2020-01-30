//=====================================
//
//YellowSpark.cpp
//機能:イエロースパーク
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "YellowSpark.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	YellowSparkControllerコンストラクタ
	***************************************/
	YellowSparkController::YellowSparkController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 20.0f, 5.0f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/YellowSpark.png");

		const unsigned MaxEmitter = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(25, 300.0f);
			emitter->CreateParticleContainer<YellowSpark>(256);
		}
	}

	/**************************************
	YellowSparkコンストラクタ
	***************************************/
	YellowSpark::YellowSpark() :
		Particle3D(10.0f, 20.0f)
	{
	}

	/**************************************
	YellowSpark初期化処理
	***************************************/
	void YellowSpark::Init()
	{
		active = true;
		cntFrame = 0.0f;


		const auto Offset = Vector3::Random();
		const float Length = Math::RandomRange(10.0f, 25.0f);

		transform->Move(Offset * Length);

		initScale = Math::RandomRange(0.5f, 1.2f);
		transform->SetScale(initScale * Vector3::One);

		const auto Diff = Vector3::Normalize({ Offset.z, Offset.y, 0.0f });
		const float Angle = Vector3::Angle(Vector3::Right, Diff);
		const D3DXVECTOR3 Axis = Vector3::Axis(Vector3::Right, Diff);

		transform->SetRotation(Quaternion::Identity);
		transform->Rotate(Angle, Axis);
	}

	/**************************************
	YellowSpark更新処理
	***************************************/
	void YellowSpark::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		float t = cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale({ initScale, scale, initScale });
	}
}