//=====================================
//
//����^�X�N����[PeriodicTask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PeriodicTask.h"
#include "../Math/TMath.h"
#include "../Core/FixedTime.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PeriodicTask::PeriodicTask(float interval, const std::function<void(void)>& task, bool ignoreTimeScale) :
	Task(task),
	cntFrame(0),
	Interval(interval),
	ignoreTimeScale(ignoreTimeScale)
{

}

/**************************************
���s����
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