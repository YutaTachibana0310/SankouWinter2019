//=====================================
//
//TitleScene.h
//機能:タイトルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
前方宣言
***************************************/
class TitleViewer;
class GameSkybox;
class TitlePlayerActor;
class TitleParticleManager;
class SkyBox;

/**************************************
クラス定義
***************************************/
class TitleScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	TitleViewer * viewer;
	TitlePlayerActor *actor;
	TitleParticleManager *particleManager;
	SkyBox *skybox;
};
#endif