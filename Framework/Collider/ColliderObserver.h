//=====================================
//
//コライダーオブザーバーヘッダ[ColliderObserver.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

#include <string>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
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