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

#include "../Actor/Enemy/DemoEnemyActor.h"
#include "../Actor/Enemy/RotateChargeEnemy.h"
#include "../Actor/Enemy/FleetEnemy.h"
#include "../Actor/Enemy/SnipeEnemyActor.h"
#include "../Actor/Enemy/MiddleWayEnemy.h"

#include <fstream>

/**************************************
�O���[�o���ϐ�
***************************************/
const unsigned EnemyData::MaxParam = 6;

/**************************************
�R���X�g���N�^
***************************************/
EnemyFactory::EnemyFactory(EnemyEventHandler **eventHandler) :
	next(0),
	count(0.0f),
	eventHandler(eventHandler)
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
	
	std::list<BaseEnemy*> output;

	for (; next < sizeContainer; next++)
	{
		EnemyData *data = dataContainer[next];

		if (data->Count() > count)
			break;

		switch (data->Type())
		{
		case RotCharge:
			CreateRotateCharge(*data, output);
			break;

		case Snipe:
			CreateSnipe(*data, output);
			break;

		case Demo:
			CreateDemo(*data, output);
			break;

		case MiddleWay:
			CreateMiddleWay(*data, output);
			break;

		case Fleet:
			CreateFleet(*data, output);
			break;
		}
	}

	return output;
}

/**************************************
��]�ːi�G�l�~�[����
***************************************/
void EnemyFactory::CreateRotateCharge(const EnemyData& data, std::list<BaseEnemy*>& output)
{
	const D3DXVECTOR3 InitPosition = { 0.0f, data.Param(0), data.Param(1)};
	const float Offset = 5.0f;
	const D3DXVECTOR3 OffsetPosition[] = {
		InitPosition,
		InitPosition + Vector3::Up * Offset,
		InitPosition + Vector3::Down * Offset,
		InitPosition + Vector3::Forward * Offset,
		InitPosition + Vector3::Back * Offset
	};

	for (int i = 0; i < 5; i++)
	{
		RotateChargeEnemy *enemy = ObjectPool::Instance()->Create<RotateChargeEnemy>(*eventHandler);
		enemy->SetPosition(OffsetPosition[i]);
		enemy->Init();

		output.push_back(enemy);
	}
}

/**************************************
�X�i�C�v�G�l�~�[����
***************************************/
void EnemyFactory::CreateSnipe(const EnemyData& data, std::list<BaseEnemy*>& output)
{
	const D3DXVECTOR3 InitPosition = { 0.0f, data.Param(0), data.Param(1) };
	const float Offset = 3.0f;
	const D3DXVECTOR3 OffsetPosition[] = {
		InitPosition,
		InitPosition + D3DXVECTOR3(0.0f, 1.0f, 1.0f) * Offset,
		InitPosition + D3DXVECTOR3(0.0f, -1.0f, 1.0f) * Offset,
		InitPosition + D3DXVECTOR3(0.0f, 1.0f, -1.0f) * Offset,
		InitPosition + D3DXVECTOR3(0.0f, -1.0f, -1.0f) * Offset
	};

	for (int i = 0; i < 5; i++)
	{
		SnipeEnemyActor *enemy = ObjectPool::Instance()->Create<SnipeEnemyActor>(*eventHandler);
		enemy->SetPosition(OffsetPosition[i]);
		enemy->Init();

		output.push_back(enemy);
	}
}

/**************************************
���^�G�l�~�[����
***************************************/
void EnemyFactory::CreateDemo(const EnemyData& data, std::list<BaseEnemy*>& output)
{
	const D3DXVECTOR3 InitPosition = { 0.0f, data.Param(0), data.Param(1) };

	DemoEnemyActor *enemy = ObjectPool::Instance()->Create<DemoEnemyActor>(*eventHandler);
	enemy->SetPosition(InitPosition);
	enemy->Init();

	output.push_back(enemy);
}

/**************************************
���^�E�F�C�G�l�~�[����
***************************************/
void EnemyFactory::CreateMiddleWay(const EnemyData& data, std::list<BaseEnemy*>& output)
{
	const D3DXVECTOR3 InitPosition = { 0.0f, data.Param(0), data.Param(1) };

	MiddleWayEnemy *enemy = ObjectPool::Instance()->Create<MiddleWayEnemy>(*eventHandler);
	enemy->SetPosition(InitPosition);
	enemy->Init();

	output.push_back(enemy);
}

/**************************************
�t���[�g�G�l�~�[����
***************************************/
void EnemyFactory::CreateFleet(const EnemyData& data, std::list<BaseEnemy*>& output)
{
	const D3DXVECTOR3 InitPosition = { 0.0f, data.Param(0), data.Param(1) };

	FleetEnemy* enemy = ObjectPool::Instance()->Create<FleetEnemy>(*eventHandler);
	enemy->SetPosition(InitPosition);
	enemy->Init();

	output.push_back(enemy);
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
		params.push_back((float)data[key].number_value());
	}
}

/**************************************
�G�l�~�[�f�[�^�f�X�g���N�^
***************************************/
EnemyData::~EnemyData()
{
	params.clear();
}
