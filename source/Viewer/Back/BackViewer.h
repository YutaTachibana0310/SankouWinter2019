//=====================================
//
//BackViewer.h
//@\:wiUIr[
//Author:GP12B332 21 §ÔY¾
//
//=====================================
#ifndef _BACKVIEWER_H_
#define _BACKVIEWER_H_

#include "../../../main.h"
#include <vector>

/**************************************
Oûé¾
***************************************/
class Polygon2D;

/**************************************
NXè`
***************************************/
class BackViewer
{
public:
	BackViewer();
	~BackViewer();

	void Draw();

	enum ViewerID
	{
		TimeBreakUpper,
		TimeBreakLower,
		ViewerMax
	};

	void PlayTimeBreak();

private:
	std::vector<Polygon2D*> viewerContainer;

	bool inPlaying;
};

#endif