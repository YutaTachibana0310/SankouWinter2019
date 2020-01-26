//=====================================
//
// EnemyFactory.cpp
// 機能:エネミーファクトリー
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyFactory.h"
#include "../../Library/json11/json11.hpp"
#include "../../Framework/Core/ObjectPool.h"

#include "EnemyTimeController.h"

#include <fstream>

/**************************************
グローバル変数
***************************************/
const unsigned EnemyData::MaxParam = 6;

/**************************************
コンストラクタ
***************************************/
EnemyFactory::EnemyFactory() :
	next(0),
	count(0.0f)
{
}

/**************************************
デストラクタ
***************************************/
EnemyFactory::~EnemyFactory()
{
	Utility::DeleteContainer(dataContainer);
}

/**************************************
読み込み処理
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
エネミー生成処理
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
回転突進エネミー生成
***************************************/
BaseEnemy * EnemyFactory::CreateRotateCharge(const EnemyData & data)
{
	return nullptr;
}

/**************************************
スナイプエネミー生成
***************************************/
BaseEnemy * EnemyFactory::CreateSnipe(const EnemyData & data)
{
	return nullptr;
}

/**************************************
中型エネミー生成
***************************************/
BaseEnemy * EnemyFactory::CreateDemo(const EnemyData & data)
{
	return nullptr;
}

/**************************************
中型ウェイエネミー生成
***************************************/
BaseEnemy * EnemyFactory::CreateMiddleWay(const EnemyData & data)
{
	return nullptr;
}

/**************************************
フリートエネミー生成
***************************************/
BaseEnemy * EnemyFactory::CreateFleet(const EnemyData & data)
{
	return nullptr;
}

/**************************************
エネミーデータコンストラクタ
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
エネミーデータデストラクタ
***************************************/
EnemyData::~EnemyData()
{
	params.clear();
}
