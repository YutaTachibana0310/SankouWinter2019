//=====================================
//
//TutorialPlayerController.h
//機能:チュートリアル用プレイヤーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALPLAYERCONTROLLER_H_
#define _TUTORIALPLAYERCONTROLLER_H_

#include "../../main.h"
#include "PlayerController.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TutorialPlayerController : public PlayerController
{
public:
	TutorialPlayerController(GameCamera *camera, BackViewer *backViewer);
	virtual ~TutorialPlayerController();

	void EnableShot(bool state);
	void EnableSlowdown(bool state);
	void EnableBomber(bool state);

private:
	bool enableShot;
	bool enableSlowdown;
	bool enableBomber;

	virtual void SlowDownEnemyBullet(bool isSlow) override;
	virtual void FireBomber() override;
	virtual void FireBullet(const D3DXVECTOR3& pos, bool isMain, int level);
};

#endif