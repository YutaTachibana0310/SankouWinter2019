//=====================================
//
//GameTelop.h
//機能:ゲーム進行に関するテロップ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMETELOP_H_
#define _GAMETELOP_H_

#include "../../../main.h"
#include <functional>

/**************************************
前方宣言
***************************************/
class Polygon2D;

/**************************************
クラス定義
***************************************/
class GameTelop : public GameObject
{
public:
	enum TelopType
	{
		GameStart,
		StageClear,
		GameOver,
		TypeMax
	};

	GameTelop();
	~GameTelop();

	void Draw();

	void Play(TelopType type, const std::function<void()>& callback);

private:
	std::shared_ptr<Polygon2D> polygon;
	std::function<void()> callback;

	void OnFinishTelopIn();
	void OnFinishTelopOut();
};
#endif