//=====================================
//
//GameSkybox.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESKYBOX_H_
#define _GAMESKYBOX_H_

#include "../../main.h"
#include "../../Framework/Renderer3D/SkyBox.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameSkybox : public SkyBox
{
public:
	GameSkybox();
	~GameSkybox();

	virtual void Update();

};
#endif