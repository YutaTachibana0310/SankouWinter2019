//=====================================
//
//BackViewer.cpp
//�@�\:�w�iUI�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackViewer.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BackViewer::BackViewer()
{
}

/**************************************
�f�X�g���N�^
***************************************/
BackViewer::~BackViewer()
{
}

/**************************************
�`�揈��
***************************************/
void BackViewer::Draw()
{
}

/**************************************
TimeBreak�Đ�����
***************************************/
void BackViewer::PlayTimeBreak()
{
	Tween::Move(*viewerContainer[TimeBreakUpper], InitPositionUpper, PositionUpper, 60, EaseType::OutCubic, true, []()
	{

	});
}
