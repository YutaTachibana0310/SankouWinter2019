//=====================================
//
//GameConfig.h
//機能:ゲーム設定
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_


/**************************************
クラス定義
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