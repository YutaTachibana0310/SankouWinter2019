//=====================================
//
// EnemyHandler.cpp
// �@�\:�G�l�~�[�o���b�g����n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyHandler.h"
#include "../../Framework/Task/TaskManager.h"

#include "../Controller/EnemyBulletController.h"
#include "../Controller/PlayerController.h"
#include "../Controller/EnemyTimeController.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyHandler::EnemyHandler(
	EnemyBulletController * bulletController,
	PlayerController *playerController) :
	bulletController(bulletController),
	playerController(playerController)
{
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyHandler::~EnemyHandler()
{
}

/**************************************
�o���b�g�Z�b�g����
***************************************/
void EnemyHandler::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	bulletController->SetBullet(shotTransform, type, speed);
}

/**************************************
WAY�e�Z�b�g����
***************************************/
void EnemyHandler::SetWayBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle)
{
	Transform transform = shotTransform;
	transform.Rotate(angle / 2.0f, Vector3::Right);

	float rotAngle = -angle / (way - 1.0f);

	for (int i = 0; i < way; i++)
	{
		bulletController->SetBullet(transform, type, speed);
		transform.Rotate(rotAngle, Vector3::Right);
	}
}

/**************************************
�~�`�e�Z�b�g����
***************************************/
void EnemyHandler::SetCircleBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way)
{
	SetWayBullet(shotTransform, type, speed, way, 360.0f);
}

/**************************************
�o���}�L�e�Z�b�g����
***************************************/
void EnemyHandler::SetStrewBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange)
{
	Transform transform = shotTransform;
	transform.Rotate(Math::RandomRange(-randomRange / 2.0f, randomRange / 2.0f), Vector3::Right);	

	bulletController->SetBullet(transform, type, speed);
}

/**************************************
�S�o���b�g��������
***************************************/
void EnemyHandler::VanishAllBullet()
{
}

/**************************************
�X�R�A�A�C�e����������
***************************************/
void EnemyHandler::GenerateScoreItem(const D3DXVECTOR3 & position)
{

}

/**************************************
�X�R�A���Z����
***************************************/
void EnemyHandler::AddScore(int point)
{

}

/**************************************
�G�l�~�[��������
***************************************/
void EnemyHandler::SlowdownEnemy()
{
	if (!inSlowdown)
		return;

	EnemyTimeController::SetTimeScale(0.01f);

	TaskManager::Instance()->CreateDelayedTask(300.0f, false, []()
	{
		EnemyTimeController::SetTimeScale(1.0f);
	});
}

/**************************************
�X���[�_�E������̕ۑ�
***************************************/
void EnemyHandler::FetchSlowdownState()
{
	inSlowdown = playerController->InSlowdown();
}

