//=====================================
//
//EnergyHandler.cpp
//�@�\:�G�i�W�[�n���h��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnergyHandler.h"
#include "../Controller/PlayerController.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnergyHandler::EnergyHandler(PlayerController * controller) :
	controller(controller)
{
}

/**************************************
�f�X�g���N�^
***************************************/
EnergyHandler::~EnergyHandler()
{
}

/**************************************
�G�i�W�[���Z����
***************************************/
void EnergyHandler::AddEnergy(float energy)
{
	controller->AddEnergy(energy);
}
