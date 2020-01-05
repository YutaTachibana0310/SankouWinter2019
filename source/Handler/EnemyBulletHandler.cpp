//=====================================
//
// EnemyBulletHandler.cpp
// �@�\:�G�l�~�[�o���b�g����n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletHandler.h"
#include "../Controller/EnemyBulletController.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletHandler::EnemyBulletHandler(EnemyBulletController * controller) :
	controller(controller)
{
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletHandler::~EnemyBulletHandler()
{
}

/**************************************
�o���b�g�Z�b�g����
***************************************/
void EnemyBulletHandler::SetBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed)
{
	controller->SetBullet(shotTransform, type, speed);
}

/**************************************
WAY�e�Z�b�g����
***************************************/
void EnemyBulletHandler::SetWayBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way, float angle)
{
	Transform transform = shotTransform;
	transform.Rotate(angle / 2.0f, Vector3::Right);

	float rotAngle = -angle / (way - 1.0f);

	for (int i = 0; i < way; i++)
	{
		controller->SetBullet(transform, type, speed);
		transform.Rotate(rotAngle, Vector3::Right);
	}
}

/**************************************
�~�`�e�Z�b�g����
***************************************/
void EnemyBulletHandler::SetCircleBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, int way)
{
	SetWayBullet(shotTransform, type, speed, way, 360.0f);
}

/**************************************
�o���}�L�e�Z�b�g����
***************************************/
void EnemyBulletHandler::SetStrewBullet(const Transform & shotTransform, EnemyBulletConfig::Type type, float speed, float randomRange)
{
	Transform transform = shotTransform;
	transform.Rotate(Math::RandomRange(-randomRange / 2.0f, randomRange / 2.0f), Vector3::Right);	

	controller->SetBullet(transform, type, speed);
}

/**************************************
�S�o���b�g��������
***************************************/
void EnemyBulletHandler::VanishAllBullet()
{
}

