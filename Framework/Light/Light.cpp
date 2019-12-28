//=====================================
//
//Light.cpp
//�@�\:���C�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Light.h"
#include "../Tool/DebugWindow.h"

#include <string>

//#define USE_LIGHTDEBUG;

namespace Light
{
	/**************************************
	�O���[�o���ϐ�
	***************************************/
	static D3DLIGHT9 light[NUM_LIGHT];
	static int NumLigt = 3;

	/**************************************
	����������
	***************************************/
	void Init()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXVECTOR3 vecDir;
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&light[0], sizeof(D3DLIGHT9));
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&light[2], sizeof(D3DLIGHT9));
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&light[1], sizeof(D3DLIGHT9));

		// ���C�g0�̐ݒ�
		light[0].Type = D3DLIGHT_DIRECTIONAL;
		light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light[0].Ambient = D3DXCOLOR(65.0f / 255.0f, 111.0f / 255.0f, 148.0f / 255.0f, 1.0f);
		vecDir = D3DXVECTOR3(-0.321f, -0.662f, 0.53f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[0].Direction, &vecDir);

		// ���C�g1�̐ݒ�
		light[1].Type = D3DLIGHT_DIRECTIONAL;
		light[1].Diffuse = D3DXCOLOR(97.0f / 255.0f, 144.0f / 255.0f, 181.0f / 255.0f, 1.0f);
		light[1].Ambient = D3DXCOLOR(60.0f / 255.0f, 132.0f / 255.0f, 154.0f / 255.0f, 1.0f);
		vecDir = D3DXVECTOR3(1.0f, -1.00f, 1.00f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[1].Direction, &vecDir);

		// ���C�g2�̐ݒ�
		light[2].Type = D3DLIGHT_DIRECTIONAL;
		light[2].Diffuse = D3DXCOLOR(56.0f / 255.0f, 80.0f / 255.0f, 123.0f / 255.0f, 1.0f);
		light[2].Ambient = D3DXCOLOR(26.0f / 255.0f, 26.0f / 255.0f, 26.0f / 255.0f, 1.0f);
		vecDir = D3DXVECTOR3(-1.00f, -1.0f, 1.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[2].Direction, &vecDir);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(0, &light[0]);
		pDevice->LightEnable(0, TRUE);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(1, &light[1]);
		pDevice->LightEnable(1, TRUE);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(2, &light[2]);
		pDevice->LightEnable(2, TRUE);

		// ���C�e�B���O���[�h
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	/**************************************
	�X�V����
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
	���C�g���擾����
	***************************************/
	D3DLIGHT9 GetData(int id)
	{
		if (id >= NUM_LIGHT)
			return D3DLIGHT9();
		else
			return light[id];
	}

	/**************************************	
	���C�g���擾����
	***************************************/
	int LightMax()
	{
		return NumLigt;
	}

}
