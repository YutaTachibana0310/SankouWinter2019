//=====================================
//
// GameViewer.h
// �@�\:�Q�[���r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEVIEWER_H_
#define _GAMEVIEWER_H_

#include "../../../main.h"
#include <functional>

/**************************************
�O���錾
***************************************/
class Polygon2D;
class ScoreViewer;
class EnergyViewer;
class BomberViewer;
class LifeViewer;
class GameTelop;

/**************************************
GameViewerParameter�N���X
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
�N���X��`
***************************************/
class GameViewer
{
public:
	GameViewer();
	~GameViewer();

	void Update();
	void Draw();

	void SetParameter(const GameViewerParameter& param);

	void PlayGameStart(const std::function<void()>& callback);
	void PlayStageClear(const std::function<void()>& callback);
	void PlayGameOvert(const std::function<void()>& callback);

private:
	Polygon2D *bg;
	ScoreViewer *scoreViewer;
	EnergyViewer *energyViewer;
	BomberViewer *bomberViewer;
	LifeViewer *lifeViewer;
	GameTelop *telop;
};

#endif