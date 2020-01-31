//=====================================
//
// EnemyFactory.h
// �@�\:�G�l�~�[�t�@�N�g���[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

#include "../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class BaseEnemy;
class EnemyData;
class EnemyEventHandler;

namespace json11
{
	class Json;
}

/**************************************
�N���X��`
***************************************/
class EnemyFactory
{
public:
	EnemyFactory(EnemyEventHandler **eventHandler);
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

	bool IsFinished();

private:
	std::vector<EnemyData*> dataContainer;
	
	unsigned int next;
	unsigned int sizeContainer;

	float count;

	EnemyEventHandler **eventHandler;


	void CreateRotateCharge(const EnemyData& data, std::list<BaseEnemy*>& output);
	void CreateSnipe(const EnemyData& data, std::list<BaseEnemy*>& output);
	void CreateDemo(const EnemyData& data, std::list<BaseEnemy*>& output);
	void CreateMiddleWay(const EnemyData& data, std::list<BaseEnemy*>& output);
	void CreateFleet(const EnemyData& data, std::list<BaseEnemy*>& output);
};

/**************************************
Data�N���X
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

	inline float Param(int no) const
	{
		return params[no];
	}

	static const unsigned MaxParam;

private:
	int type;
	float count;
	std::vector<float> params;
};

#endif