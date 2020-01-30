//=====================================
//
//GameScore.cpp
//�@�\:�Q�[���X�R�A
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScore.h"
#include "../../Framework/Core/PlayerPrefs.h"
#include "../GameConfig.h"

/**************************************
�X�R�A���Z����
***************************************/
void GameScore::AddScore(unsigned int point)
{
	score += (int)(point * (1.0f * combo * 0.025f));
}

/**************************************
�X�R�A�擾����
***************************************/
void GameScore::AddCombo()
{
	++combo;
}

/**************************************
�X�R�A�擾����
***************************************/
unsigned int GameScore::Score() const
{
	return score;
}

/**************************************
����������
***************************************/
void GameScore::Init()
{
	score = 0;
	combo = 0;
}

/**************************************
�Z�[�u����
***************************************/
void GameScore::Save()
{
	std::string saveKey = std::string(NAMEOF_ENUM(GameConfig::SaveKey::CurrentScore));
	PlayerPrefs::SaveNumber<unsigned int>(saveKey, score);
}

/**************************************
�R���{���Z�b�g
***************************************/
void GameScore::ResetCombo()
{
	combo = 0;
}
