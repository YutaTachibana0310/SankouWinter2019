//=====================================
//
// BomberViewer.h
// �@�\:�{���o�[�r���[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOMBERVIEWER_H_
#define _BOMBERVIEWER_H_

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
class BomberViewer : public TextViewer
{
public:
	BomberViewer();
	~BomberViewer();

	void Update();
	void Draw();

	void SetCount(int num);

private:
	std::vector<Polygon2D*> container;
	int count;
};

#endif