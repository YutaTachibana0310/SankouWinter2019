//=====================================
//
//遅延タスク処理[DelayedTask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "DelayedTask.h"
#include "../Core/FixedTime.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
DelayedTask::DelayedTask(float delay, const std::function<void(void)>& task, bool ignoreTimeScale) :
	cntFrame(0),
	Delay(delay),
	Task(task),
	ignoreTimeScale(ignoreTimeScale)
{

}

/**************************************
実行処理
***************************************/
void DelayedTask::Run()
{
	if (state != State::Idle)
		return;

	if (ignoreTimeScale)
		cntFrame += 1.0f;
	else
		cntFrame += FixedTime::GetTimeScale();

	if (cntFrame >= Delay)
	{
		func();
		state = State::Finished;
	}
}
