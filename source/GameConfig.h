//=====================================
//
//GameConfig.h
//�@�\:�Q�[���ݒ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_


/**************************************
�N���X��`
***************************************/
class GameConfig
{
public:
	enum SceneID
	{
		Game,
		Title,
		Result,
		SceneMax
	};

	enum SaveKey
	{
		RecordNum,
		Ranking,
		CurrentScore
	};
};
#endif