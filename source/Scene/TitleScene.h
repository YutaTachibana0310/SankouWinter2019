//=====================================
//
//TitleScene.h
//�@�\:�^�C�g���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
�O���錾
***************************************/
class TitleViewer;
class GameSkybox;
class TitlePlayerActor;
class TitleParticleManager;
class SkyBox;

/**************************************
�N���X��`
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