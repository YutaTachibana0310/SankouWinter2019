//=====================================
//
//定期タスクヘッダ[PeriodicTask.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PERIODICTASK_H_
#define _PERIODICTASK_H_

#include "Task.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
PeriodicTaskクラス
***************************************/
class PeriodicTask : public Task
{
public:
	//コンストラクタ
	PeriodicTask(
		float interval, 
		const std::function<void(void)>& task,
		bool ignoreTimeScale);	

private:	
	void Run();			//実行処理

	float cntFrame;		//フレームカウント
	const float Interval;	//インターバル
	bool ignoreTimeScale;
};

#endif