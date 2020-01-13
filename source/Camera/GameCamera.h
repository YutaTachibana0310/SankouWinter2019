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

#include <functional>

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

	bool Focus(const D3DXVECTOR3& position, const std::function<void()>& callback);

	static const D3DXVECTOR3 InitPosition;
	static const float DurationFocusTransition;
	static const int DurationFocus;

private:
	int cntFocus;
	bool inFocus;

	std::shared_ptr<float> tweenViewAngle;
	std::function<void()> callback;
};
#endif