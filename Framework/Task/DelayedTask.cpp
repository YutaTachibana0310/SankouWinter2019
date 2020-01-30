//=====================================
//
//�x���^�X�N����[DelayedTask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "DelayedTask.h"
#include "../Core/FixedTime.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
DelayedTask::DelayedTask(float delay, const std::function<void(void)>& task, bool ignoreTimeScale) :
	cntFrame(0),
	Delay(delay),
	Task(task),
	ignoreTimeScale(ignoreTimeScale)
{

}

/**************************************
���s����
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
