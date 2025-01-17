//=====================================
//
// MoveTweener.h
// 機能:移動トゥイーナー
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MOVETWEENER_H_
#define _MOVETWEENER_H_

#include "../../../main.h"
#include "Tweener.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MoveTweener : public Tweener<Transform>
{
public:
	/**************************************
	コンストラクタ
	***************************************/
	MoveTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, bool ignoreTimeScale, Callback callback) :
		Tweener<Transform>(ref, duration, type, ignoreTimeScale, callback),
		start(start),
		end(end)
	{
	}

	/**************************************
	更新処理
	***************************************/
	void Update()
	{
		CountUp();

		std::shared_ptr<Transform> transform = reference.lock();
		if (transform)
		{
			float t = cntFrame / duration;
			transform->SetPosition(Easing::EaseValue(t, start, end, easeType));
			CheckCallback();
		}
	}

private:
	D3DXVECTOR3 start, end;
};

#endif