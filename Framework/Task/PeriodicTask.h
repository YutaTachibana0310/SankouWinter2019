//=====================================
//
//����^�X�N�w�b�_[PeriodicTask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PERIODICTASK_H_
#define _PERIODICTASK_H_

#include "Task.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
PeriodicTask�N���X
***************************************/
class PeriodicTask : public Task
{
public:
	//�R���X�g���N�^
	PeriodicTask(
		float interval, 
		const std::function<void(void)>& task,
		bool ignoreTimeScale);	

private:	
	void Run();			//���s����

	float cntFrame;		//�t���[���J�E���g
	const float Interval;	//�C���^�[�o��
	bool ignoreTimeScale;
};

#endif