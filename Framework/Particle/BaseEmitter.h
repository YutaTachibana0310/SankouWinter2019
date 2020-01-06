//=====================================
//
//ベースエミッタヘッダ[BaseEmitter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../../main.h"
#include "BaseParticle.h"

#include <vector>
#include <functional>

/**************************************
BaseEmitterクラス
***************************************/
class BaseParticle;

class BaseEmitter : public GameObject
{
public:
	BaseEmitter();
	BaseEmitter(int emitNum);
	BaseEmitter(int emitNum, float duration);
	BaseEmitter(int emitNum, float durationMin, float durationMax);
	BaseEmitter(int emitNumMin, int emitNumMax, float durationMin, float durationMax);

	virtual ~BaseEmitter();

	virtual void Init(std::function<void(void)>& callback);
	virtual void Update();
	virtual bool Emit(std::vector<BaseParticle*>& container);

	virtual bool IsActive() const override;

	virtual void UseCulling(bool value);

protected:
	float cntFrame;
	float duration;
	int emitNum;
	bool useCull;
	float prevEmitTime;

	std::function<void(void)> callback;
};

#endif