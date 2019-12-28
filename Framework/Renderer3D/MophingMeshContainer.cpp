//=====================================
//
//MorphingMeshContainer.cpp
//�@�\:���[�t�B���O���b�V���R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MophingMeshContainer.h"
#include "../Effect/MophingEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
***************************************/
MorphingMeshContainer::MorphingMeshContainer() :
	indexBuff(NULL),
	declare(NULL),
	effect(NULL),
	currentIndex(-1), nextIndex(-1), t(0.0f)
{
	effect = new MophingEffect();
}

/**************************************
�f�X�g���N�^
***************************************/
MorphingMeshContainer::~MorphingMeshContainer()
{
	for (auto&& mesh : meshTable)
	{
		SAFE_RELEASE(mesh);
	}

	for (auto&& container : textureContainer)
	{
		for (auto&& tex : container)
		{
			SAFE_RELEASE(tex);
		}
	}

	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(declare);

	SAFE_DELETE(effect);

	materialContainer.clear();
	attributeTable.clear();
}

/**************************************
���b�V���o�^����
***************************************/
void MorphingMeshContainer::RegisterVertex(unsigned index)
{
	if (mesh == NULL)
		return;

	if (meshTable.size() < index + 1)
	{
		meshTable.resize(index + 1, NULL);
		textureContainer.resize(index + 1);
		materialContainer.resize(index + 1);
	}

	//�o�b�t�@�o�^
	meshTable[index] = mesh;
	meshTable[index]->AddRef();
	fvf = mesh->GetFVF();

	if (indexBuff == NULL)
		mesh->GetIndexBuffer(&indexBuff);

	//�}�e���A���o�^
	materialContainer[index].reserve(materialNum);
	for (unsigned i = 0; i < materialNum; i++)
	{
		materialContainer[index].push_back(materials[i]);
	}

	//�e�N�X�`���o�^
	textureContainer[index].resize(materialNum);
	for(unsigned i = 0; i < materialNum; i++)
	{
		textureContainer[index][i] = textures[i];

		if(textures[i] != NULL)
			textures[i]->AddRef();
	}


	//�����e�[�u���擾
	if (attributeTable.empty())
	{
		attributeTable.resize(materialNum);
		mesh->GetAttributeTable(&attributeTable[0], NULL);
	}

	//���_�錾�쐬
	if (declare == NULL)
	{
		D3DVERTEXELEMENT9 elem[65];
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		ZeroMemory(elem, sizeof(D3DVERTEXELEMENT9) * 65);
		mesh->GetDeclaration(elem);

		for (int i = 0; i < 65; i++)
		{
			if (elem[i].Type != D3DDECLTYPE_UNUSED)
				continue;

			for (int j = i; j < i * 2; j++)
			{
				elem[j] = elem[j - i];
				elem[j].Stream = 1;
				elem[j].UsageIndex = 1;
			}
			elem[i * 2] = D3DDECL_END();
			break;
		}

		HRESULT res = pDevice->CreateVertexDeclaration(elem, &declare);
		assert(res == S_OK);
	}

	//�C���f�b�N�X�ݒ�
	if (currentIndex < 0)
	{
		nextIndex = currentIndex = index;
	}
}

/**************************************
�`�揈��
***************************************/
void MorphingMeshContainer::Draw(const D3DXMATRIX & mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���b�V�����璸�_�o�b�t�@���擾
	LPDIRECT3DVERTEXBUFFER9 vtx0, vtx1;
	meshTable[currentIndex]->GetVertexBuffer(&vtx0);
	meshTable[nextIndex]->GetVertexBuffer(&vtx1);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, vtx0, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, vtx1, 0, D3DXGetFVFVertexSize(fvf));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(indexBuff);

	//���_�錾�ݒ�
	pDevice->SetVertexDeclaration(declare);

	//�V�F�[�_�փp�����[�^��ݒ�
	effect->SetWorld(mtxWorld);
	effect->SetTime(t);

	//�`��
	for (unsigned i = 0; i < materialNum; i++)
	{
		effect->SetMaterial(materialContainer[currentIndex][i]);
		effect->SetNextMaterial(materialContainer[nextIndex][i]);

		pDevice->SetTexture(0, textureContainer[currentIndex][i]);
		effect->SetNextTexture(textureContainer[nextIndex][i]);

		effect->Begin();
		effect->BeginPass(0);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0,
			attributeTable[i].VertexStart,
			attributeTable[i].VertexCount,
			attributeTable[i].VertexStart * 3,
			attributeTable[i].FaceCount);

		effect->EndPass();
		effect->End();
	}
}

/**************************************
���݂̃��b�V���I������
***************************************/
void MorphingMeshContainer::SetCurrent(unsigned index)
{
	if (index < 0 || index >= meshTable.size())
		return;

	currentIndex = index;
}

/**************************************
���̃��b�V���I������
***************************************/
void MorphingMeshContainer::SetNext(unsigned next)
{
	if (next < 0 || next >= meshTable.size())
		return;

	nextIndex = next;
}

/**************************************
�ω��ʐݒ菈��
***************************************/
void MorphingMeshContainer::SetChange(float t)
{
	this->t = t;
}

/**************************************
�o�^�������b�V�������
***************************************/
void MorphingMeshContainer::ReleaseRegistration()
{
	//���b�V�����
	for (auto&& mesh : meshTable)
	{
		SAFE_RELEASE(mesh);
	}
	meshTable.clear();

	//�e�N�X�`�����
	for (auto&& container : textureContainer)
	{
		for (auto&& texture : container)
		{
			SAFE_RELEASE(texture);
		}
		container.clear();
	}
	textureContainer.clear();

	//�}�e���A�����
	for (auto&& container : materialContainer)
	{
		container.clear();
	}
	materialContainer.clear();

	//�C���f�b�N�X�o�b�t�@���
	SAFE_RELEASE(indexBuff);

	//���_�錾���
	SAFE_RELEASE(declare);
	fvf = 0;

	//���_�����e�[�u�����
	attributeTable.clear();

	currentIndex = nextIndex = -1;
}

/**************************************
Draw()���֎~���邽�߂�private��
***************************************/
void MorphingMeshContainer::Draw() {}

/**************************************
Draw()���֎~���邽�߂�private��
***************************************/
void MorphingMeshContainer::Draw(RendererEffect & effect) {}
