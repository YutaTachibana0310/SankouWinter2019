//=====================================
//
//ヘキサポップトランジション処理[HexaPopTransitionMask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "HexaPopTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"

using namespace std;
/**************************************
staticメンバ
***************************************/
const int HexaPopTransitionMask::DivineX = 10;
const int HexaPopTransitionMask::DivineY = 10;
const float HexaPopTransitionMask::Duration = 1.0f;
const float HexaPopTransitionMask::Interval = 0.16f;

typedef BaseTransitionMask Base;
/**************************************
コンストラクタ
***************************************/
HexaPopTransitionMask::HexaPopTransitionMask()
{
	polygon = new Polygon2D();

	//ポリゴンの大きさを計算
	float sizeX = (float)SCREEN_WIDTH / DivineX;
	float sizeY = (float)SCREEN_HEIGHT / DivineY;
	polygon->SetSize({ sizeX, sizeY });
	polygon->LoadTexture("data/TRANSITION/HexaMask.png");

	//X方向1列で一つのベクターとして
	//2次元配列のようにベクターのベクターを作る
	for (int y = 0; y < DivineY + 2; y++)
	{
		vector<Hexagon*> list;
		for (int x = 0; x < DivineX + 3; x++)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(x * sizeX, (y - 1) * sizeY, 0.0f);

			if (x % 2 != 0)
				pos.y += sizeY * 0.5f;

			list.push_back(new Hexagon(pos));
		}
		hexList.push_back(list);
	}

	//各列のベクターに対してのイテレータを初期化
	itrList.resize(hexList.size());
	for (UINT i = 0; i < itrList.size(); i++)
	{
		itrList[i] = hexList[i].begin();
	}
}

/**************************************
デストラクタ
***************************************/
HexaPopTransitionMask::~HexaPopTransitionMask()
{
	for (auto& list : hexList)
	{
		Utility::DeleteContainer(list);
	}
	hexList.clear();

	SAFE_DELETE(polygon);
}

/**************************************
更新処理
***************************************/
MaskResult HexaPopTransitionMask::Update()
{
	if (!active)
		return MaskResult::Continuous;

	//更新処理の結果
	MaskResult result = MaskResult::Continuous;

	//初期化を開始する行を指すインデックスの更新
	int interval = (int)(FramePerSecond * Interval);
	if (cntFrame++ % interval == 0)	
		rowIndex = Math::Clamp((UINT)0, (UINT)hexList.size(), ++rowIndex);

	//六角形を初期化
	for (UINT y = 0; y < rowIndex; y++)
	{
		if (itrList[y] != hexList[y].end())
		{
			(*itrList[y])->Init();
			itrList[y]++;
		}
	}

	//六角形を更新
	for (auto& list : hexList)
	{
		for (auto& hex : list)
		{
			hex->Update(*this);
		}
	}

	//全ての六角形のイージングが終了していたら終了通知を返す
	if (isFinished)
	{
		active = false;
		result = isTransitionOut ? MaskResult::FinishTransitionOut : FinishTransitionIn;
	}

	return result;
}

/**************************************
描画処理更新処理
***************************************/
void HexaPopTransitionMask::Draw()
{
	if (!active)
		return;

	//マスク開始
	Base::BeginMask();

	//マスク領域描画
	for (auto& list : hexList)
	{
		for (auto& hex : list)
		{
			polygon->SetTransform(hex->transform);
			polygon->Draw();
		}
	}

	//マスク終了
	Base::EndMask();
}

/**************************************
セット処理
***************************************/
void HexaPopTransitionMask::Set(bool isTransitionOut)
{
	if (active)
		return;

	//イージング用のパラメータ初期化
	startScale = isTransitionOut ? D3DXVECTOR3(0.0f, 0.0f, 0.0f) : D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	endScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f) - startScale;
	type = isTransitionOut ? EaseType::OutSine : EaseType::InSine;
	cntFrame = 0;

	//ヘキサリスト初期化
	for (auto& list : hexList)
	{
		for (auto& hex : list)
		{
			hex->active = false;
			hex->transform.SetScale(startScale);
		}
	}

	//フラグ初期化
	active = true;
	this->isTransitionOut = isTransitionOut;
	isFinished = false;

	//カウント初期化
	cntFrame = 0;
	rowIndex = 0;
	
	//イテレータ初期化
	for (UINT i = 0; i < itrList.size(); i++)
	{
		itrList[i] = hexList[i].begin();
	}
}

/**************************************
Hexagonコンストラクタ
***************************************/
HexaPopTransitionMask::Hexagon::Hexagon(D3DXVECTOR3 pos)
{
	transform.SetPosition(pos);
	cntFrame = 0;
	active = false;
}

/**************************************
Hexagon初期化処理
***************************************/
void HexaPopTransitionMask::Hexagon::Init()
{
	cntFrame = 0;
	active = true;
}

/**************************************
Hexagon更新処理
***************************************/
void HexaPopTransitionMask::Hexagon::Update(HexaPopTransitionMask& parent)
{
	if (!active)
		return;

	//イージング
	cntFrame++;
	float t = ((float)cntFrame / FramePerSecond) / Duration;
	transform.SetScale(Easing::EaseValue(t, parent.startScale, parent.endScale, parent.type));

	//終了判定
	if (t >= Duration && IsLastHexa(parent))
		parent.isFinished = true;
}

/**************************************
Hexagon終端確認
***************************************/
bool HexaPopTransitionMask::Hexagon::IsLastHexa(HexaPopTransitionMask& parent)
{
	return  *((parent.hexList.end() - 1)->end() - 1) == this;
}