//=====================================
//
//GameTelop.h
//�@�\:�Q�[���i�s�Ɋւ���e���b�v
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMETELOP_H_
#define _GAMETELOP_H_

#include "../../../main.h"
#include <functional>

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
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