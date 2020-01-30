//=====================================
//
//TitleParticleManager.cpp
//機能:タイトルパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Task/TaskManager.h"
#include "../../Framework/PostEffect/ScreenObject.h"

#include "Game\PlayerTrail.h"

/**************************************
初期化処理
***************************************/
void TitleParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(TitleEffect::Max, nullptr);

	controllers[TitleEffect::PlayerTrail] = new Effect::Game::PlayerTrailController();

	crossFilter->SetPower(1.0f, 1.0f, 1.0f);
	crossFilter->SetThrethold(0.46f, 0.35f, 0.18f);
}
