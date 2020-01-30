//=====================================
//
//GameParticleManager.cpp
//�@�\:�Q�[���p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Task/TaskManager.h"
#include "../../Framework/PostEffect/ScreenObject.h"

#include "../Handler/EnergyHandler.h"

#include "Game\PlayerBulletHit.h"
#include "Enemy\EnemyExplosion.h"
#include "Enemy/EnemyDebris.h"
#include "Game/PlayerExplosion.h"
#include "Enemy/EnemyFlame.h"
#include "Enemy/EnemySmallDebris.h"
#include "Enemy\EnemyBulletVanish.h"
#include "Enemy\EnemyTrail.h"
#include "Game\PlayerTrail.h"
#include "Game\EnergyEffect.h"
#include "Game\ScoreEffect.h"
#include "Game\YellowSpark.h"
#include "Game\YellowBomber.h"

/**************************************
static�����o
***************************************/
const float GameParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float GameParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
����������
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameEffect::Max);
	controllers[GameEffect::PlayerBulletHit] = new Effect::Game::PlayerBulletHitController();
	controllers[GameEffect::EnemyExplosion] = new Effect::Game::EnemyExplosionController();
	controllers[GameEffect::EnemyDebris] = new Effect::Game::EnemyDebrisController();
	controllers[GameEffect::PlayerExplosion] = new Effect::Game::PlayerExplosionController();
	controllers[GameEffect::EnemyFlame] = new Effect::Game::EnemyFlameController();
	controllers[GameEffect::EnemySmallDebris] = new Effect::Game::EnemySmallDebrisController();
	controllers[GameEffect::EnemyBulletVanish] = new Effect::Game::EnemyBulletVanishController();
	controllers[GameEffect::EnemyTrail] = new Effect::Game::EnemyTrailController();
	controllers[GameEffect::PlayerTrail] = new Effect::Game::PlayerTrailController();
	controllers[GameEffect::YellowSpark] = new Effect::Game::YellowSparkController();
	controllers[GameEffect::YellowBomber] = new Effect::Game::YellowBomberController();

	scoreEffectController = new Effect::Game::ScoreEffectController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
�I������
***************************************/
void GameParticleManager::Uninit()
{
	SAFE_DELETE(energyEffectController);
	SAFE_DELETE(scoreEffectController);
	SceneParticleManager::Uninit();
}

/**************************************
�X�V����
***************************************/
void GameParticleManager::Update()
{
	scoreEffectController->Update();
	energyEffectController->Update();
	SceneParticleManager::Update();
}

/**************************************
�G�i�W�[�G�t�F�N�g�`�揈��
***************************************/
void GameParticleManager::DrawEnergyEffect()
{
	BaseParticleController::BeginDraw();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ChangeRenderParameter();

	bool isDrewd = false;

	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	isDrewd |= energyEffectController->Draw();
	isDrewd |= scoreEffectController->Draw();
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	BaseParticleController::EndDraw();

	RestoreRenderParameter();
	screenObj->Draw();

	if (isDrewd)
	{
		crossFilter->Draw(renderTexture);
	}

	//SceneParticleManager::Draw();
}

/**************************************
�G�l�~�[�̔����ݒ菈��
***************************************/
void GameParticleManager::GenerateEnemyExplosion(const D3DXVECTOR3 & position)
{
	controllers[GameEffect::EnemyExplosion]->SetEmitter(position);
	controllers[GameEffect::EnemyDebris]->SetEmitter(position);
}

/**************************************
�G�l�~�[�̏������ݒ菈��
***************************************/
void GameParticleManager::GenerateEnemySmallExplositon(const D3DXVECTOR3 & position)
{
	controllers[GameEffect::EnemyFlame]->SetEmitter(position);
	controllers[GameEffect::EnemySmallDebris]->SetEmitter(position);
}

/**************************************
�G�l�~�[�̑唚���ݒ菈��
***************************************/
void GameParticleManager::GenerateEnemyBigExplosion(const D3DXVECTOR3 & position)
{
	GenerateEnemyExplosion(position);

	const float OffsetRangeX = 2.0f;
	const float OffsetRangeY = 10.0f;
	const float OffsetRangeZ = 15.0f;

	for (int i = 0; i < 5; i++)
	{
		D3DXVECTOR3 offsetPosition = position;
		offsetPosition.x += Math::RandomRange(-OffsetRangeX, OffsetRangeX);
		offsetPosition.y += Math::RandomRange(-OffsetRangeY, OffsetRangeY);
		offsetPosition.z += Math::RandomRange(-OffsetRangeZ, OffsetRangeZ);

		TaskManager::Instance()->CreateDelayedTask(i* 2.0f, true, [&, offsetPosition]()
		{
			GenerateEnemyExplosion(offsetPosition);
		});
	}
}

/**************************************
�G�i�W�[�G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::GenerateEnergyEffect(const D3DXVECTOR3 & position, float energy)
{
	energyEffectController->SetEmitter(position, energy);
}

/**************************************
�X�R�A�G�t�F�N�g�R���g���[���쐬����
***************************************/
void GameParticleManager::GenerateScoreEffect(const D3DXVECTOR3 & position, int point)
{
	scoreEffectController->SetEmitter(position, point);
}

/**************************************
�{���o�[�G�t�F�N�g�Z�b�g
***************************************/
void GameParticleManager::GenerareBomber(const D3DXVECTOR3 position)
{
	controllers[GameEffect::YellowSpark]->SetEmitter(position);
	controllers[GameEffect::YellowBomber]->SetEmitter(position);
}

/**************************************
�G�i�W�[�G�t�F�N�g�R���g���[���쐬����
***************************************/
void GameParticleManager::CreateEnergyEffectController(const std::shared_ptr<EnergyHandler>& energyHandler)
{
	energyEffectController = new Effect::Game::EnergyEffectController(energyHandler);
}
