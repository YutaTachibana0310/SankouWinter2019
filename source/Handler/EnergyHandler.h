//=====================================
//
//EnergyHandler.h
//�@�\:�G�i�W�[�n���h��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENERGYHANDLER_H_
#define _ENERGYHANDLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class PlayerController;

/**************************************
�N���X��`
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