//=====================================
//
//定期タスク処理[PeriodicTask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PeriodicTask.h"
#include "../Math/TMath.h"
#include "../Core/FixedTime.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
PeriodicTask::PeriodicTask(float interval, const std::function<void(void)>& task, bool ignoreTimeScale) :
	Task(task),
	cntFrame(0),
	Interval(interval),
	ignoreTimeScale(ignoreTimeScale)
{

}

/**************************************
実行処理
***************************************/
void PeriodicTask::Run()
{
	if (state != State::Idle)
		return;

	if (!ignoreTimeScale)
		cntFrame += FixedTime::GetTimeScale();
	else
		cntFrame += 1.0f;

	if (cntFrame >= Interval)
	{
		cntFrame -= Interval;
		func();
	}
}