//=====================================
//
// EnemyBulletController.h
// 機能:エネミーバレットコントローラ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETCONTROLLER_H_
#define _ENEMYBULLETCONTROLLER_H_

#include "../../main.h"
#include "EnemyBulletConfig.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class EnemyBulletActor;

/**************************************
クラス定義
***************************************/
class EnemyBulletController
{
public:
	EnemyBulletController();
	~EnemyBulletController();

	void Update();
	void Draw();
	
	void SetBullet(const Transform& shotTransform, EnemyBulletConfig::Type type, float speed);

	void DisableAllBullet();

	static const unsigned MaxBullet;

private:
	class BulletRenderer;

	std::vector<EnemyBulletActor*> bulletContainer;
	unsigned cntBullet;

	BulletRenderer *renderer;
};

/**************************************
EnemyBulletActor描画用クラス
***************************************/
class EnemyBulletController::BulletRenderer
{
public:
	BulletRenderer(EnemyBulletController *entity);
	~BulletRenderer();

	void Draw();

private:
	EnemyBulletController *entity;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DVERTEXBUFFER9 transformBuffer;
	LPDIRECT3DVERTEXBUFFER9 uvBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPDIRECT3DVERTEXDECLARATION9 declare;
	LPD3DXEFFECT effect;
	D3DXHANDLE hMtxView, hMtxProjection, hMtxInvView;
	LPDIRECT3DTEXTURE9 texture;

	int cntBullet;

	void LoadEffect();
	void MakeVtxBuffer();
	void MakeDeclaration();
	void MakeTransformBuffer();
	void MakeUVBuffer();
	void MakeIndexBuffer();

	void SetTransformBuffer();
	void SetUVBuffer();
};

#endif