//=====================================
//
// PlanetActor.h
// �@�\:�f���A�N�^�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLANETACTOR_H_
#define _PLANETACTOR_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;

/**************************************
�N���X��`
***************************************/
class PlanetActor : public GameObject
{
public:
	PlanetActor();
	virtual ~PlanetActor();

	void Update();
	void Draw();

	static const D3DXVECTOR3 InitPos;

private:
	MeshContainer *mesh;
};

#endif