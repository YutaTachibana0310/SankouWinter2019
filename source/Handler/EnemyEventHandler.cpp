//=====================================
//
// EventHandler.cpp
// �@�\:�G�l�~�[�o���b�g����n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyEventHandler.h"
#include "../../Framework/Task/TaskManager.h"

#include "../Controller/EnemyBulletController.h"
#include "../Controller/PlayerController.h"
#include "../Controller/EnemyTimeController.h"
#include "../Viewer/Back/BackViewer.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyEventHandler::EnemyEventHandler() :
	bulletController(bulletController),
	playerController(playerController)
{
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyEventHandler::~EnemyEventHandler()
{
}

/**************************************
�o���b�g�Z�b�g����
***************************************/
void EnemyEventHandler::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	bulletController->SetBullet(shotTransform, type, speed);
}

/**************************************
WAY�e�Z�b�g����
***************************************/
void EnemyEventHandler::SetWayBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle)
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
void EnemyEventHandler::SetCircleBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way)
{
	SetWayBullet(shotTransform, type, speed, way, 360.0f);
}

/**************************************
�o���}�L�e�Z�b�g����
***************************************/
void EnemyEventHandler::SetStrewBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange)
{
	Transform transform = shotTransform;
	transform.Rotate(Math::RandomRange(-randomRange / 2.0f, randomRange / 2.0f), Vector3::Right);	

	bulletController->SetBullet(transform, type, speed);
}

/**************************************
�S�o���b�g��������
***************************************/
void EnemyEventHandler::VanishAllBullet()
{
}

/**************************************
�X�R�A�A�C�e����������
***************************************/
void EnemyEventHandler::GenerateScoreItem(const D3DXVECTOR3 & position)
{

}

/**************************************
�X�R�A���Z����
***************************************/
void EnemyEventHandler::AddScore(int point)
{

}

/**************************************
�G�l�~�[��������
***************************************/
void EnemyEventHandler::SlowdownEnemy()
{
	if (!inSlowdown)
		return;

	backViewer->PlayTimeBreak();
	EnemyTimeController::SetTimeScale(0.01f);

	TaskManager::Instance()->CreateDelayedTask(300.0f, false, []()
	{
		EnemyTimeController::SetTimeScale(1.0f);
	});
}

/**************************************
�X���[�_�E������̕ۑ�
***************************************/
void EnemyEventHandler::FetchSlowdownState()
{
	inSlowdown = playerController->InSlowdown();
}

/**************************************
�G�l�~�[�o���b�g�R���g���[���ݒ菈��
***************************************/
void EnemyEventHandler::GiveEnemyBulletController(EnemyBulletController * controller)
{
	bulletController = controller;
}

/**************************************
�v���C���[�R���g���[���ݒ菈��
***************************************/
void EnemyEventHandler::GivePlayerController(PlayerController * controller)
{
	playerController = controller;
}

/**************************************
�o�b�N�r���[���ݒ菈��
***************************************/
void EnemyEventHandler::GiveBackViewer(BackViewer * viewer)
{
	backViewer = viewer;
}

