//=====================================
//
//GameCamera.h
//�@�\:�Q�[���J����
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMECAMERA_H_
#define _GAMECAMERA_H_

#include "../../main.h"
#include "../../Framework/Camera/Camera.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameCamera : public Camera
{
public:
	GameCamera();
	~GameCamera();

	void Update() override;

	void Focus(const D3DXVECTOR3& position);

	static const D3DXVECTOR3 InitPosition;

private:
	int cntFocus;
	bool inFocus;

	std::shared_ptr<float> tweenViewAngle;
};
#endif