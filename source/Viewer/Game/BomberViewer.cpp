//=====================================
//
// BomberViewer.cpp
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BomberViewer.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BomberViewer::BomberViewer() :
	TextViewer("BadFennec", 40),
	count(5)
{
	transform->SetPosition({ 600.0f, 30.0f, 0.0f });

	SetHorizontalAlignment(HorizontalAlignment::Right);
	SetText("BOMBER");

	UseOutLine(true);
	SetOutlineColor({ 0.5f, 0.0f, 0.0f, 1.0f });
	SetOutlineWidth(5);

	container.resize(5, nullptr);
	for (unsigned i = 0; i < container.size(); i++)
	{
		container[i] = new Polygon2D();
		Polygon2D *entity = container[i];

		entity->LoadTexture("data/TEXTURE/Viewer/bomIcon.png");

		D3DXVECTOR3 position = D3DXVECTOR3(575.0f, 75.0f, 0.0f) + Vector3::Left * 50.0f * (float)i;
		entity->SetPosition(position);
		entity->SetSize({ 25.0f, 25.0f });
	}
}

/**************************************
�f�X�g���N�^
***************************************/
BomberViewer::~BomberViewer()
{
	Utility::DeleteContainer(container);
}

/**************************************
�X�V����
***************************************/
void BomberViewer::Update()
{
}

/**************************************
�`�揈��
***************************************/
void BomberViewer::Draw()
{
	TextViewer::Draw();

	for (int i = 0; i < count; i++)
	{
		container[i]->Draw();
	}
}

/**************************************
�J�E���g�ݒ菈��
***************************************/
void BomberViewer::SetCount(int num)
{
	count = num;
}
