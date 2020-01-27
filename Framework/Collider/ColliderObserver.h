//=====================================
//
//�R���C�_�[�I�u�U�[�o�[�w�b�_[ColliderObserver.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ColliderObserver
{
public:
	virtual void OnColliderHit(ColliderObserver *other) = 0;

	inline std::string Tag() const
	{
		return tag;
	}

	void SetTag(const std::string& tag)
	{
		this->tag = tag;
	}

private:
	std::string tag;
};

#endif