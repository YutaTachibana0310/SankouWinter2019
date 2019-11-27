//=====================================
//
//�V�[���p�[�e�B�N���}�l�[�W������[SceneParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SceneParticleManager.h"
#include "../PostEffect/CrossFilterController.h"
#include "../PostEffect/ScreenObject.h"
#include "BaseParticleController.h"
#include "../PostEffect/CrossFilterController.h"
#include "../Tool/DebugWindow.h"
#include "../../Library/cppLinq/cpplinq.hpp"

/**************************************
�}�N����`
***************************************/
#define SCENEMPARTICLEMANAGER_LABEL		"ParticleManager"

/**************************************
�R���X�g���N�^
***************************************/
SceneParticleManager::SceneParticleManager() :
	renderTexture(NULL),
	renderSurface(NULL),
	screenObj(NULL),
	oldSuf(NULL),
	initialized(false)
{
}

/**************************************
����������
***************************************/
void SceneParticleManager::Init()
{
	//�V���O���g�����̂��߁A�����Ń��\�[�X���쐬
	if (!initialized)
	{
		CreateRenderTarget();
		initialized = true;
		crossFilter = new CrossFilterController();
	}
}

/**************************************
�I������
***************************************/
void SceneParticleManager::Uninit()
{
	for (auto& controller : controllers)
	{
		controller->Uninit();
	}

	//�V���O���g���̂��߂����Ń��\�[�X���
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
	SAFE_DELETE(crossFilter);

	Utility::DeleteContainer(controllers);

	initialized = false;
}

/**************************************
�X�V����
***************************************/
void SceneParticleManager::Update()
{
	for (auto& controller : controllers)
	{
		controller->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void SceneParticleManager::Draw()
{
	using cpplinq::from;
	using cpplinq::where;
	using cpplinq::to_vector;

	//�C���X�^���V���O�`��J�n
	BaseParticleController::BeginDraw();

	//�N���X�t�B���^��K�p���Ȃ�3D�p�[�e�B�N����`��
	{
		auto controller = from(controllers)
			>> where([](BaseParticleController* entity)
		{
			return !entity->UseCrossFilter() && entity->GetType() == BaseParticleController::Particle_3D;
		})
			>> to_vector();

		for (auto&& entity : controller)
		{
			entity->Draw();
		}
	}

	//�����_�[�p�����[�^�؂�ւ�
	ChangeRenderParameter();

	//�`��t���O
	bool isDrewd = false;

	//3D���ɕ`��
	auto controller3D = from(controllers)
		>> where([](BaseParticleController* controller)
	{
		return controller->GetType() == BaseParticleController::Particle_3D;
	})
		>> to_vector();

	for (auto& controller : controller3D)
	{
		isDrewd |= controller->Draw();
	}

	//2D����ɕ`��
	auto controller2D = from(controllers)
		>> where([](BaseParticleController* controller)
	{
		return controller->GetType() == BaseParticleController::Particle_2D;
	})
		>> to_vector();

	for (auto& controller : controller2D)
	{
		isDrewd |= controller->Draw();
	}

	//�C���X�^���V���O�`��I��
	BaseParticleController::EndDraw();

	//���̃����_�[�^�[�Q�b�g�ɕ���
	RestoreRenderParameter();
	screenObj->Draw();

	//�����[�X�ł̂݃N���X�t�B���^��K�p����
#ifndef _DEBUG	
	if (isDrewd)
		crossFilter->Draw(renderTexture);
#endif

	//�N���X�t�B���^��K�p���Ȃ�2D�p�[�e�B�N����`��
	{
		BaseParticleController::BeginDraw();

		auto controller = from(controllers)
			>> where([](BaseParticleController* entity)
		{
			return !entity->UseCrossFilter() && entity->GetType() == BaseParticleController::Particle_2D;
		})
			>> to_vector();

		for (auto&& entity : controller)
		{
			entity->Draw();
		}

		BaseParticleController::EndDraw();
	}
}

/**************************************
��������
***************************************/
BaseEmitter* SceneParticleManager::Generate(UINT id, const D3DXVECTOR3& pos, std::function<void(void)> callback)
{
	if (id < 0 || id >= controllers.size())
		return nullptr;

	return controllers[id]->SetEmitter(pos, callback);
}

/**************************************
��������
***************************************/
BaseEmitter* SceneParticleManager::Generate(UINT id, const Transform& transform, std::function<void(void)> callback)
{
	if (id < 0 || id >= controllers.size())
		return nullptr;

	return controllers[id]->SetEmitter(transform, callback);
}

/**************************************
�����_�[�^�[�Q�b�g�쐬����
***************************************/
void SceneParticleManager::CreateRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�쐬
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	//�T�[�t�F�C�X�擾
	renderTexture->GetSurfaceLevel(0, &renderSurface);

	//�r���[�|�[�g�쐬
	pDevice->GetViewport(&viewPort);
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;

	//�`��p�X�N���[���I�u�W�F�N�g�쐬
	screenObj = new ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************
�����_�[�p�����[�^�ύX����
***************************************/
void SceneParticleManager::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g���L���b�V��
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->GetViewport(&oldViewport);

	//�����_�[�^�[�Q�b�g�؂�ւ�
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);
}

/**************************************
�����_�[�p�����[�^��������
***************************************/
void SceneParticleManager::RestoreRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}