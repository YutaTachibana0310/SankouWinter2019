//=====================================
//
//AnimationResource.h
//�@�\:�A�j���[�V����Resources
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ANIMATIONRESOURCE_H_
#define _ANIMATIONRESOURCE_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class AnimContainer;

/**************************************
�N���X��`
***************************************/
class AnimationResource
{
public:
	AnimationResource();
	virtual ~AnimationResource();

	HRESULT Load(const char* fileName, const char* errorSrc);

	void Clone(AnimContainer* container);

private:
	LPD3DXFRAME rootFrame;
	LPD3DXANIMATIONCONTROLLER animController;

	int animSetNum;

	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME frameBase, LPD3DXFRAME frameRoot);
};
#endif