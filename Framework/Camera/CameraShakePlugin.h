//=====================================
//
//�J�����V�F�C�N�v���O�C���w�b�_[ShakePlugin.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERASHAKEPLUGIN_H_
#define _CAMERASHAKEPLUGIN_H_

#include "Camera.h"
#include "../Pattern/BaseSingleton.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class CameraShakePlugin : public BaseCameraPlugin, public BaseSingleton<CameraShakePlugin>
{
	friend class BaseSingleton<CameraShakePlugin>;
public:
	void Update();
	void Apply(Transform& work);
	void Set(const D3DXVECTOR3& amplitude, int duration = 30);

private:
	int cntFrame;
	D3DXVECTOR3 amplitude;
	int duration;
	bool active;
	
	CameraShakePlugin();
	CameraShakePlugin(const CameraShakePlugin&) {}
	~CameraShakePlugin() {}
};

#endif