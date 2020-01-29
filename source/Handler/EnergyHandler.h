//=====================================
//
//EnergyHandler.h
//機能:エナジーハンドラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENERGYHANDLER_H_
#define _ENERGYHANDLER_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class PlayerController;

/**************************************
クラス定義
***************************************/
class EnergyHandler
{
public:
	EnergyHandler(PlayerController *controller);
	~EnergyHandler();

	void AddEnergy(float energy);

private:
	PlayerController * controller;
};

#endif