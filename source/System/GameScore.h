//=====================================
//
//GameScore.h
//�@�\:�Q�[���X�R�A
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCORE_H_
#define _GAMESCORE_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
���ߐ؂肪��΂��̂ŃV���O���g���ɂ��Ă��܂�
�{���͂����Ɛ݌v������
***************************************/
class GameScore : public BaseSingleton<GameScore>
{
public:
	void AddScore(unsigned int point);
	void AddCombo();

	unsigned int Score() const;

	void Init();

	void Save();

	void ResetCombo();

private:
	unsigned int score;
	unsigned int combo;
};
#endif