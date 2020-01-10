//=====================================
//
//遅延タスクヘッダ[DelayedTask.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DELAYEDTASK_H_
#define _DELAYEDTASK_H_

#include "Task.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
DelayedTaskクラス
***************************************/
class DelayedTask : public Task
{
public:
	//コンストラクタ
	DelayedTask(
		float delay, 
		const std::function<void(void)>& task,
		bool ignoreTimeScale);

private:
	void Run();			//実行処理
	
	float cntFrame;		//フレームカウント
	const float Delay;	//遅延フレーム
	bool ignoreTimeScale;
};

#endif