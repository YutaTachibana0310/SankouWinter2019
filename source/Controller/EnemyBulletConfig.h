//=====================================
//
// EnemyBulletConfig.h
// �@�\:�G�l�~�[�o���b�g�ݒ�
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETCONFIG_H_
#define _ENEMYBULLETCONFIG_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyBulletConfig
{
public:
	//�o���b�g�^�C�v
	enum Type
	{
		RedRotate,
		RedLarge,
		RedSphere,
		RedNeedle,
		BlueRotate,
		BlueLarge,
		BlueSphere,
		BlueNeedle,
		EnemyBulletMax
	};

	static int GetTextureIndex(Type type, int indexAnim);
	static int GetBloomTextureIndex(Type type, int indexAnim);

private:
	EnemyBulletConfig() {}
	~EnemyBulletConfig() {}

	static const int PeriodAnimation;
};

#endif