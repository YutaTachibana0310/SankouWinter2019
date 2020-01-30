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
#include <functional>

/**************************************
前方宣言
***************************************/
class ResultViewer;
class ScoreRanking;
class RankingViewer;
class BloomController;

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