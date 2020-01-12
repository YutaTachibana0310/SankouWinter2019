//=====================================
//
// GameViewer.h
// 機能:ゲームビューワ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEVIEWER_H_
#define _GAMEVIEWER_H_

#include "../../../main.h"

/**************************************
前方宣言
***************************************/
class Polygon2D;
class ScoreViewer;
class EnergyViewer;
class BomberViewer;
class LifeViewer;

/**************************************
GameViewerParameterクラス
***************************************/
class GameViewerParameter
{
public:
	float percentEnergy;
	int cntLife;
	int cntBomb;

	GameViewerParameter(float percentEnergy, int cntLife, int cntBomb) :
		percentEnergy(percentEnergy),
		cntLife(cntLife),
		cntBomb(cntBomb)
	{
		
	}
};

/**************************************
クラス定義
***************************************/
class GameViewer
{
public:
	GameViewer();
	~GameViewer();

	void Update();
	void Draw();

	void SetParameter(const GameViewerParameter& param);

private:
	Polygon2D *bg;
	ScoreViewer *scoreViewer;
	EnergyViewer *energyViewer;
	BomberViewer *bomberViewer;
	LifeViewer *lifeViewer;
};

#endif