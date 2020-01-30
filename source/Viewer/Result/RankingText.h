//=====================================
//
//RankingText.h
//�@�\:�����L���O�e�L�X�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RANKINGTEXT_H_
#define _RANKINGTEXT_H_

#include "../../../main.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class RankingInfo;

/**************************************
�N���X��`
***************************************/
class RankingText : public TextViewer
{
public:
	RankingText();
	~RankingText();

	void Draw() override;

	void MoveIn(float delay);

	void SetScore(const RankingInfo& info);

	static const int SizeFont;

private:
	TextViewer * scoreText;
};
#endif