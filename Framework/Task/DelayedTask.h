//=====================================
//
//�x���^�X�N�w�b�_[DelayedTask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DELAYEDTASK_H_
#define _DELAYEDTASK_H_

#include "Task.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
DelayedTask�N���X
***************************************/
class DelayedTask : public Task
{
public:
	//�R���X�g���N�^
	DelayedTask(
		float delay, 
		const std::function<void(void)>& task,
		bool ignoreTimeScale);

private:
	void Run();			//���s����
	
	float cntFrame;		//�t���[���J�E���g
	const float Delay;	//�x���t���[��
	bool ignoreTimeScale;
};

#endif