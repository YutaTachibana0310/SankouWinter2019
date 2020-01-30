//=====================================
//
//TutorialPlayerController.h
//�@�\:�`���[�g���A���p�v���C���[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALPLAYERCONTROLLER_H_
#define _TUTORIALPLAYERCONTROLLER_H_

#include "../../main.h"
#include "PlayerController.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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