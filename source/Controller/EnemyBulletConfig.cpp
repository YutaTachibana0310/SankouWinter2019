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

/**************************************
�e�N�X�`���ʂ��ԍ��擾
***************************************/
int EnemyBulletConfig::GetTextureIndex(Type type, int indexAnim)
{
	int bias = type * PeriodAnimation * 2;
	int index = indexAnim % PeriodAnimation;

	return bias + index;
}
