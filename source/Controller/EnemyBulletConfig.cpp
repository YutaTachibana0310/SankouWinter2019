//=====================================
//
// EnemyBulletConfig.cpp
// �@�\:�G�l�~�[�o���b�g�ݒ�
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletConfig.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const int EnemyBulletConfig::PeriodAnimation = 4;
const D3DXVECTOR2 EnemyBulletConfig::SizePolygon = { 2.0f, 2.0f };
const D3DXVECTOR2 EnemyBulletConfig::SplitTexture = { 8.0f, 8.0f };

/**************************************
�e�N�X�`���ʂ��ԍ��擾
***************************************/
int EnemyBulletConfig::GetTextureIndex(Type type, int indexAnim)
{
	int bias = type * PeriodAnimation * 2;
	int index = indexAnim % PeriodAnimation;

	return bias + index;
}

/**************************************
�u���[���e�N�X�`���ʂ��ԍ��擾
***************************************/
int EnemyBulletConfig::GetBloomTextureIndex(Type type, int indexAnim)
{
	int bias = type * PeriodAnimation * 2 + PeriodAnimation;
	int index = indexAnim % PeriodAnimation;

	return bias + index;
}
