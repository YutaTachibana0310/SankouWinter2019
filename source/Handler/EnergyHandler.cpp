//=====================================
//
//EnergyHandler.cpp
//機能:エナジーハンドラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnergyHandler.h"
#include "../Controller/PlayerController.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
EnergyHandler::EnergyHandler(PlayerController * controller) :
	controller(controller)
{
}

/**************************************
デストラクタ
***************************************/
EnergyHandler::~EnergyHandler()
{
}

/**************************************
エナジー加算処理
***************************************/
void EnergyHandler::AddEnergy(float energy)
{
	controller->AddEnergy(energy);
}
