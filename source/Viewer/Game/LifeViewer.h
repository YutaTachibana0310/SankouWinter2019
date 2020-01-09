//=====================================
//
// LifeViewer.h
// �@�\:�c�@�r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _LIFEVIEWER_H_
#define _LIFEVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Renderer2D/TextViewer.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
***************************************/
class LifeViewer : public TextViewer
{
public:
	LifeViewer();
	~LifeViewer();

	void Update();
	void Draw();

	void SetCount(int num);

private:
	int count;
	std::vector<Polygon2D*> container;
};

#endif