//=====================================
//
//PlayerBomber.h
//�@�\:�v���C���[�{���o�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBOMBER_H_
#define _PLAYERBOMBER_H_

#include "../../../main.h"
#include "../../../Framework/Collider/BaseCollider.h"

/**************************************
�O���錾
***************************************/
class BoxCollider3D;

/**************************************
�N���X��`
***************************************/
class PlayerBomberActor : public GameObject, public ColliderObserver
{
public:
	PlayerBomberActor();
	~PlayerBomberActor();

	void Init();
	void Uninit();
	void Update();

	virtual void OnColliderHit(ColliderObserver * other) override;

private:
	std::shared_ptr<BoxCollider3D> collider;
	float cntFrame;

};
#endif