//=============================================================================
//
// メイン処理 [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
// windows.hの中にwinsock.hをインクルードするので
// WinSock2.hのインクルード順番はWindows.hの前じゃないとコンパイルエラーになる
#include <WinSock2.h>	// Network用
#include <windows.h>
#include "d3dx9.h"
#include "Framework\Core\Transform.h"
#include "Framework\Core\GameObject.h"
#include "Framework\Math\TMath.h"
#include "Framework\Math\Vector3.h"
#include "Framework\Core\Utility.h"
#include "Framework/Core/FixedTime.h"

#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include "dinput.h"
#include <tchar.h>
#include <stdio.h>
#include <assert.h>
#include <process.h>	// MultiThread用

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "ws2_32.lib")	// WinSockで必要
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ビルボード頂点フォーマット
#define FVF_VERTEX_BILLBOARD	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//　マテリアルを使用する板ポリゴンフォーマット
#define FVF_VERTEX_MATERIAL		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)

#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

//解放、削除関連
#define SAFE_RELEASE(p)				{if(p) {p->Release();	p = NULL;}}
#define SAFE_DELETE(p)				{if(p) {delete(p);		p = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[](p);	p = NULL;}}

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;

// 上記ビルボードフォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標0
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_BILLBOARD;

// 上記マテリアルポリゴンフォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_MATERIAL;

//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#else
//#define new new
//#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LPDIRECT3DTEXTURE9 CreateTextureFromFile(LPSTR szName, LPDIRECT3DDEVICE9 lpD3DDevice);
#endif