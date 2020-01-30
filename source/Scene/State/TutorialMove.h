//=====================================
//
//TutorialMove.h
//機能:移動チュートリアル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALMOVE_H_
#define _TUTORIALMOVE_H_

#include "../../../main.h"
#include "../TutorialScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TutorialScene::TutorialMove : public TutorialScene::TutorialState
{
public:
	void OnStart(TutorialScene& entity);
	State OnUpdate(TutorialScene& entity);
};
#endif