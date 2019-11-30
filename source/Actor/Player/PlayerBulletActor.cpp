//=====================================
//
//PlayerBulletActor.cpp
//機能:プレイヤーバレットアクター
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Camera/Camera.h"

/**************************************
staticメンバ
***************************************/
const float PlayerBulletActor::SpeedMove = 2.0f;
const D3DXVECTOR2 PlayerBulletActor::Size = { 2.0f, 1.0f };

/**************************************
コンストラクタ
***************************************/
PlayerBulletActor::PlayerBulletActor()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("PlayerBullet", polygon);
}

/**************************************
デストラクタ
***************************************/
PlayerBulletActor::~PlayerBulletActor()
{
	SAFE_DELETE(polygon);
}

/**************************************
初期化処理
***************************************/
void PlayerBulletActor::Init(const D3DXVECTOR3& position)
{
	active = true;
	transform->SetPosition(position);
}

/**************************************
終了処理
***************************************/
void PlayerBulletActor::Uninit()
{
}

/**************************************
更新処理
***************************************/
void PlayerBulletActor::Update()
{
	transform->Move(Vector3::Right * SpeedMove);

	if (_IsOutBorder())
	{
		active = false;
	}
}

/**************************************
描画処理
***************************************/
void PlayerBulletActor::Draw()
{
	polygon->Draw(transform->GetMatrix());
}

/**************************************
<演算子
***************************************/
bool PlayerBulletActor::operator<(const PlayerBulletActor & rhs) const
{
	return transform->GetPosition().z < rhs.GetPosition().z;
}

/**************************************
>演算子
***************************************/
bool PlayerBulletActor::operator>(const PlayerBulletActor & rhs) const
{
	return transform->GetPosition().z > rhs.GetPosition().z;
}

/**************************************
移動範囲チェック処理
***************************************/
bool PlayerBulletActor::_IsOutBorder()
{
	D3DXVECTOR3 position = transform->GetPosition();

	D3DXVECTOR3 leftTop = Camera::MainCamera()->Projection(position + D3DXVECTOR3(-Size.x, Size.y, 0.0f));
	if (leftTop.x < 0.0f || leftTop.y < -SCREEN_HEIGHT * 0.1f)
		return true;

	D3DXVECTOR3 rightBottom = Camera::MainCamera()->Projection(position + D3DXVECTOR3(Size.x, -Size.y, 0.0f));
	if(rightBottom.x > SCREEN_WIDTH * 1.05f || rightBottom.y > SCREEN_HEIGHT * 1.1f)
		return true;

	return false;
}
