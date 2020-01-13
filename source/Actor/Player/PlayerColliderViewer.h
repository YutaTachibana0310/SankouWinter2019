//=====================================
//
// PlayerColliderVIewer.h
// �@�\:�v���C���[�̓����蔻��r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERCOLLIDERVIEWER_H_
#define _PLAYERCOLLIDERVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"

/**************************************
�O���錾
***************************************/
class BoardPolygon;

/**************************************
�N���X��`
***************************************/
class PlayerColliderViewer : public BillboardObject
{
public:
	PlayerColliderViewer();
	~PlayerColliderViewer();

	void Update();
	void Draw();

	static const int PeriodAnimation;
	static const int MaxAnimation;

private:
	BoardPolygon *polygon;

	int cntFrame;
	int animIndex;
};

#endif