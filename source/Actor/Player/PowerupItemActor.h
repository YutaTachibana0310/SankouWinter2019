//=====================================
//
//PowerupItemActor.h
//�@�\:�p���[�A�b�v�A�C�e���A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _POWEUPITEMACTOR_H_
#define _POWEUPITEMACTOR_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/BillboardObject.h"

/**************************************
�O���錾
***************************************/
class BoxCollider3D;
class BoardPolygon;

/**************************************
�N���X��`
***************************************/
class PowerupItemActor : public BillboardObject
{
public:
	PowerupItemActor();
	~PowerupItemActor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	static const D3DXVECTOR3 MoveBorder;

private:
	BoardPolygon * polygon;

	D3DXVECTOR3 moveDir;
	float cntFrame;
};

#endif