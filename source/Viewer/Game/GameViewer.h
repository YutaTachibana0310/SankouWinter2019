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

/**************************************
�O���錾
***************************************/
class Polygon2D;
class ScoreViewer;
class EnergyViewer;
class BomberViewer;
class LifeViewer;

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

private:
	Polygon2D *bg;
	ScoreViewer *scoreViewer;
	EnergyViewer *energyViewer;
	BomberViewer *bomberViewer;
	LifeViewer *lifeViewer;
};

#endif