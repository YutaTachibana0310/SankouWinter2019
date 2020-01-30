//=====================================
//
//ResultScene.h
//�@�\:���U���g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include <functional>

/**************************************
�O���錾
***************************************/
class ResultViewer;
class ScoreRanking;
class RankingViewer;
class BloomController;

/**************************************
�N���X��`
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
	ScoreRanking *ranking;
	RankingViewer *rankViewer;
	BloomController *bloom;

	std::shared_ptr<float> bloomPower;

	bool inTransition;

	void OnFinishBlinkIn();
	void OnFinishBlinkOut();

	std::function<void()> onFinishBlinkIn;
	std::function<void()> onFinishBlinkOut;
};
#endif