//=====================================
//
//Light.cpp
//機能:ライト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Light.h"
#include "../Tool/DebugWindow.h"

#include <string>

//#define USE_LIGHTDEBUG;

namespace Light
{
	/**************************************
	グローバル変数
	***************************************/
	static D3DLIGHT9 light[NUM_LIGHT];
	static int NumLigt = 3;

	/**************************************
	初期化処理
	***************************************/
	void Init()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXVECTOR3 vecDir;
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&light[0], sizeof(D3DLIGHT9));
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&light[2], sizeof(D3DLIGHT9));
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&light[1], sizeof(D3DLIGHT9));

		// ライト0の設定
		light[0].Type = D3DLIGHT_DIRECTIONAL;
		light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light[0].Ambient = D3DXCOLOR(65.0f / 255.0f, 111.0f / 255.0f, 148.0f / 255.0f, 1.0f);
		vecDir = D3DXVECTOR3(-0.321f, -0.662f, 0.53f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[0].Direction, &vecDir);

		// ライト1の設定
		light[1].Type = D3DLIGHT_DIRECTIONAL;
		light[1].Diffuse = D3DXCOLOR(97.0f / 255.0f, 144.0f / 255.0f, 181.0f / 255.0f, 1.0f);
		light[1].Ambient = D3DXCOLOR(60.0f / 255.0f, 132.0f / 255.0f, 154.0f / 255.0f, 1.0f);
		vecDir = D3DXVECTOR3(1.0f, -1.00f, 1.00f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[1].Direction, &vecDir);

		// ライト2の設定
		light[2].Type = D3DLIGHT_DIRECTIONAL;
		light[2].Diffuse = D3DXCOLOR(56.0f / 255.0f, 80.0f / 255.0f, 123.0f / 255.0f, 1.0f);
		light[2].Ambient = D3DXCOLOR(26.0f / 255.0f, 26.0f / 255.0f, 26.0f / 255.0f, 1.0f);
		vecDir = D3DXVECTOR3(-1.00f, -1.0f, 1.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[2].Direction, &vecDir);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(0, &light[0]);
		pDevice->LightEnable(0, TRUE);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(1, &light[1]);
		pDevice->LightEnable(1, TRUE);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(2, &light[2]);
		pDevice->LightEnable(2, TRUE);

		// ライティングモード
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	/**************************************
	更新処理
	***************************************/
	void Update()
	{
#ifdef USE_LIGHTDEBUG
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		Debug::Begin("Light");

		for (int i = 0; i < NumLigt; i++)
		{
			std::string tagDir = "Light" + std::to_string(i);
			D3DXVECTOR3 dir = light[i].Direction;
			Debug::Slider(tagDir.c_str(), dir, Vector3::One * -1.0f, Vector3::One);
			light[i].Direction = (D3DVECTOR)dir;

			std::string tagDiffuse = "Diffuse" + std::to_string(i);
			D3DXCOLOR color = light[i].Diffuse;
			Debug::ColorEdit(tagDiffuse.c_str(), color);
			light[i].Diffuse = color;

			std::string tagAmbient = "Ambient" + std::to_string(i);
			color = light[i].Ambient;
			Debug::ColorEdit(tagAmbient.c_str(), color);
			light[i].Ambient = color;

			pDevice->SetLight(i, &light[i]);

			Debug::NewLine();
		}

		D3DCAPS9 caps;
		pDevice->GetDeviceCaps(&caps);
		Debug::Text("MaxLight:%d", caps.MaxActiveLights);

		Debug::End();
#endif
	}

	/**************************************
	ライト情報取得処理
	***************************************/
	D3DLIGHT9 GetData(int id)
	{
		if (id >= NUM_LIGHT)
			return D3DLIGHT9();
		else
			return light[id];
	}

	/**************************************	
	ライト数取得処理
	***************************************/
	int LightMax()
	{
		return NumLigt;
	}

}
