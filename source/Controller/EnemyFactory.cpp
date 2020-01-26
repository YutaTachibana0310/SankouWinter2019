//=====================================
//
// EnemyFactory.cpp
// �@�\:�G�l�~�[�t�@�N�g���[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyFactory.h"
#include "../../Library/json11/json11.hpp"
#include "../../Framework/Core/ObjectPool.h"

#include "EnemyTimeController.h"

#include <fstream>

/**************************************
�O���[�o���ϐ�
***************************************/
const unsigned EnemyData::MaxParam = 6;

/**************************************
�R���X�g���N�^
***************************************/
EnemyFactory::EnemyFactory() :
	next(0),
	count(0.0f)
{
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyFactory::~EnemyFactory()
{
	Utility::DeleteContainer(dataContainer);
}

/**************************************
�ǂݍ��ݏ���
***************************************/
void EnemyFactory::Load(const char * path)
{
	std::ifstream ifs("data/DATA/EnemyData.json", std::ios::in);
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	std::string err;
	auto datas = json11::Json::parse(json, err).array_items();

	sizeContainer = datas.size();
	dataContainer.reserve(sizeContainer);
	for (auto&& data : datas)
	{
		EnemyData *enemyData = new EnemyData(data);
		dataContainer.push_back(enemyData);
	}
}

/**************************************
�G�l�~�[��������
***************************************/
std::list<BaseEnemy*> EnemyFactory::Create()
{
	count += EnemyTimeController::GetBulletTimeScale();

	EnemyData* data = dataContainer[next];
	
	std::list<BaseEnemy*> output;

	for (unsigned i = next; i < sizeContainer; i++)
	{
		BaseEnemy* enemy = nullptr;
		switch (data->Type())
		{
		case RotCharge:
			enemy = CreateRotateCharge(*data);
			break;

		case Snipe:
			enemy = CreateSnipe(*data);
			break;

		case Demo:
			enemy = CreateDemo(*data);
			break;

		case MiddleWay:
			enemy = CreateMiddleWay(*data);
			break;

		case Fleet:
			enemy = CreateFleet(*data);
			break;
		}

		if (enemy != nullptr)
			output.push_back(enemy);
	}

	return output;
}

/**************************************
��]�ːi�G�l�~�[����
***************************************/
BaseEnemy * EnemyFactory::CreateRotateCharge(const EnemyData & data)
{
	return nullptr;
}

/**************************************
�X�i�C�v�G�l�~�[����
***************************************/
BaseEnemy * EnemyFactory::CreateSnipe(const EnemyData & data)
{
	return nullptr;
}

/**************************************
���^�G�l�~�[����
***************************************/
BaseEnemy * EnemyFactory::CreateDemo(const EnemyData & data)
{
	return nullptr;
}

/**************************************
���^�E�F�C�G�l�~�[����
***************************************/
BaseEnemy * EnemyFactory::CreateMiddleWay(const EnemyData & data)
{
	return nullptr;
}

/**************************************
�t���[�g�G�l�~�[����
***************************************/
BaseEnemy * EnemyFactory::CreateFleet(const EnemyData & data)
{
	return nullptr;
}

/**************************************
�G�l�~�[�f�[�^�R���X�g���N�^
***************************************/
EnemyData::EnemyData(const json11::Json & data) :
	count((float)data["Count"].number_value())
{
	const std::string dataType = data["Type"].string_value();

	if (dataType == "RotCharge")
		type = 0;
	else if (dataType == "Snipe")
		type = 1;
	else if (dataType == "Demo")
		type = 2;
	else if (dataType == "MiddleWay")
		type = 3;
	else if (dataType == "Fleet")
		type = 4;
	else
		type = -1;
	
	params.reserve(MaxParam);
	for (int i = 0; i <= MaxParam; i++)
	{
		std::string key = "Param";
		key += std::to_string(i);
		params.push_back(data[key].string_value());
	}
}

/**************************************
�G�l�~�[�f�[�^�f�X�g���N�^
***************************************/
EnemyData::~EnemyData()
{
	params.clear();
}
