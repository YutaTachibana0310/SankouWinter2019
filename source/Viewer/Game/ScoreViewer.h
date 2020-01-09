//=====================================
//
// ScoreViewer.h
// �@�\:�X�R�A�r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCOREVIEWER_H_
#define _SCOREVIEWER_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class TextViewer;

/**************************************
�N���X��`
***************************************/
class ScoreViewer
{
public:
	ScoreViewer();
	~ScoreViewer();

	void Update();
	void Draw();

	void SetScore(int score);

private:
	TextViewer *caption;
	TextViewer *num;
};

#endif