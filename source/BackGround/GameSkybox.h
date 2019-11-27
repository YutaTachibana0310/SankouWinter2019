//=====================================
//
//GameSkybox.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESKYBOX_H_
#define _GAMESKYBOX_H_

#include "../../main.h"
#include "../../Framework/Renderer3D/SkyBox.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameSkybox : public SkyBox
{
public:
	GameSkybox();
	~GameSkybox();

	virtual void Update();

};
#endif