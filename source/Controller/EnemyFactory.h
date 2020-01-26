//=====================================
//
// EnemyFactory.h
// 機能:エネミーファクトリー
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

#include "../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class BaseEnemy;
class EnemyData;

namespace json11
{
	class Json;
}

/**************************************
クラス定義
***************************************/
class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();

	void Load(const char* path);

	 std::list<BaseEnemy*> Create();

	 enum EnemyType
	 {
		 RotCharge,
		 Snipe,
		 Demo,
		 MiddleWay,
		 Fleet
	 };

private:
	std::vector<EnemyData*> dataContainer;
	
	unsigned int next;
	unsigned int sizeContainer;

	float count;

	BaseEnemy* CreateRotateCharge(const EnemyData& data);
	BaseEnemy* CreateSnipe(const EnemyData& data);
	BaseEnemy* CreateDemo(const EnemyData& data);
	BaseEnemy* CreateMiddleWay(const EnemyData& data);
	BaseEnemy* CreateFleet(const EnemyData& data);
};

/**************************************
Dataクラス
***************************************/
class EnemyData
{
public:
	EnemyData(const json11::Json& data);
	~EnemyData();

	inline float Count() const
	{
		return count;
	}

	inline int Type() const
	{
		return type;
	}

	inline std::string Param(int no) const
	{
		return params[no];
	}

	static const unsigned MaxParam;

private:
	int type;
	float count;
	std::vector<std::string> params;
};

#endif