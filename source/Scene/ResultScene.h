//=====================================
//
//ResultScene.h
//機能:リザルトシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
***************************************/
class ResultViewer;

/**************************************
クラス定義
***************************************/
class ResultScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	ResultViewer * viewer;
};
#endif