//=====================================
//
//GameCamera.h
//機能:ゲームカメラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMECAMERA_H_
#define _GAMECAMERA_H_

#include "../../main.h"
#include "../../Framework/Camera/Camera.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
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