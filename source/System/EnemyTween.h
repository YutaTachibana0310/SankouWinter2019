//=====================================
//
//トゥイーンヘッダ[Transformween.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYTWEEN_H_
#define _ENEMYTWEEN_H_

#include "../../main.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Core/Transform.h"

#include <list>
#include <memory>
#include <iterator>
#include <functional>

/**************************************
前方宣言
***************************************/
class BaseEnemy;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/

class EnemyTween
{
	friend class EnemyController;
public:
	/**************************************
	移動トゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 start : 移動開始座標
	引数 end : 移動先座標
	引数 duration : 移動にかける時間
	引数 type : イージングタイプ
	引数 callback : 終了時のコールバック関数
	***************************************/
	static void Move(BaseEnemy& ref, const D3DXVECTOR3& startPosition, const D3DXVECTOR3& endPosition, float duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	移動トゥイーン
	基本的には上記と一緒だが、移動開始座標を現在座標に自動で設定してくれる
	***************************************/
	static void Move(BaseEnemy& ref, const D3DXVECTOR3& endPosition, float duratino, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	スケールトゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 start : 開始時のスケール
	引数 end : 終了時のスケール
	引数 duration : スケールにかける時間
	引数 type : イージングタイプ
	引数 callback : 終了時のコールバック関数
	***************************************/
	static void Scale(BaseEnemy& ref, const D3DXVECTOR3& startScale, const D3DXVECTOR3& endScale, float duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	スケールトゥイーン
	基本的には上記と一緒だが開始時のスケールを現在スケールに自動で設定してくれる
	***************************************/
	static void Scale(BaseEnemy& ref, const D3DXVECTOR3& endScale, float duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	回転トゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 start : 回転開始角度（オイラー角）
	引数 end : 回転終了角度（オイラー角）
	引数 duration : 回転にかける時間
	引数 type : イージングタイプ
	引数 callback : 終了時のコールバック関数
	※回転角度は自動で0.0f~360.0fに補正されてしまうので注意
	***************************************/
	static void Rotate(BaseEnemy& ref, const D3DXVECTOR3& startEulerAngle, const D3DXVECTOR3& endEulerAngle, float duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	回転トゥイーン
	基本的には上記と一緒だが開始の回転角度を自動で現在角度に設定してくれる
	***************************************/
	static void Rotate(BaseEnemy& ref, const D3DXVECTOR3& endEulaerAngle, float duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	方向トゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 endDirection : 回転終了時の前方向
	引数 duration : 回転にかける時間
	引数 type : イージングタイプ
	引数 dummyAxis : 始点の向きと終点の向きが平行だった場合に使用する回転軸
	引数 callback : 終了時のコールバック関数
	***************************************/
	static void Turn(BaseEnemy& ref, const D3DXVECTOR3& endDirection, float duration, EaseType type, const D3DXVECTOR3& dummyAxis, std::function<void()> callback = nullptr);

private:
	void Update();
	void ClearContainer();
	void ClearAll();

	class EnemyTweener;
	std::list<EnemyTween::EnemyTweener*> tweenerContainer;

	static EnemyTween* mInstance;
	EnemyTween();
	~EnemyTween();

	using Callback = std::function<void(void)>;

	class EnemyTweener
	{
	public:
		EnemyTweener(std::shared_ptr<Transform>& ref, float duration, EaseType type, Callback callback);
		virtual ~EnemyTweener();
		inline bool IsFinished();
		virtual void Update() = 0;
		inline void CheckCallback();

	protected:
		std::weak_ptr<Transform> reference;
		float cntFrame;
		float duration;
		EaseType type;
		Callback callback;
	};

	class MoveEnemyTweener : public EnemyTweener
	{
	public:
		MoveEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback);
		void Update();

	private:
		D3DXVECTOR3 start, end;
	};

	class ScaleEnemyTweener : public EnemyTweener
	{
	public:
		ScaleEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback);
		void Update();

	private:
		D3DXVECTOR3 start, end;
	};

	class RotateEnemyTweener : public EnemyTweener
	{
	public:
		RotateEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback);
		RotateEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXQUATERNION& start, const D3DXQUATERNION& end, float duration, EaseType type, Callback callback);
		void Update();

	private:
		D3DXQUATERNION start, end;
	};
};

#endif