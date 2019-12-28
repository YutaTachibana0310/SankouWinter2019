//=====================================
//
//�V�[���}�l�[�W������[SceneManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "SceneManager.h"
#include "BaseScene.h"
#include "../Resource/ResourceManager.h"
#include "../Tool/ProfilerCPU.h"
#include "../Tween/Tween.h"
#include "../Sound/SoundEffect.h"
#include "../Sound/BackgroundMusic.h"
#include "../Core/ObjectPool.h"
#include "../Task/TaskManager.h"

using namespace std;
/**************************************
static�����o
***************************************/
SceneManager* SceneManager::mInstance = NULL;

/**************************************
�R���X�g���N�^
***************************************/
SceneManager::SceneManager() :
	current(NULL),
	prev(NULL)
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

/**************************************
�f�X�g���N�^
***************************************/
SceneManager::~SceneManager()
{
	Utility::DeleteMap(sceneContainer);

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

/**************************************
�V�[���`�F���W����
***************************************/
void SceneManager::ChangeScene(const int sceneID)
{
	//�V�[���̑��݊m�F
	if (!mInstance->ExistsScene(sceneID))
	{
		MessageBox(0, "NextScene is Not Found", "Error", 0);
		return;
	}

	//�V�[���؂�ւ�
	mInstance->_ChengeScene(sceneID);
}

/**************************************
�V�[���`�F���W����(����)
***************************************/
void SceneManager::_ChengeScene(const int sceneID)
{
	//���݂̃V�[�����I��
	if (current != NULL)
	{
		current->Uninit();
		ObjectPool::Instance()->ClearAll();
		ResourceManager::Instance()->AllRelease();
		ProfilerCPU::Instance()->Clear();
		Tween::mInstance->ClearAll();
		TaskManager::Instance()->ClearAll();

		//NOTE:�d�������H
		//BGM::Clear();
		//SE::Clear();
	}

	//�؂�ւ�
	prev = current;
	current = sceneContainer[sceneID];

	//������
	current->Init();
}

/**************************************
�V�[���ǉ�����
***************************************/
void SceneManager::Add(const int sceneID, BaseScene* scene)
{
	if (ExistsScene(sceneID))
		return;

	sceneContainer[sceneID] = scene;
}

/**************************************
�X�V����
***************************************/
void SceneManager::Update()
{
	current->Update();
}

/**************************************
�`�揈��
***************************************/
void SceneManager::Draw()
{
	current->Draw();
}

/**************************************
�V�[���I������
***************************************/
void SceneManager::Uninit()
{
	//���݂̃V�[�����I��
	if (current != NULL)
	{
		current->Uninit();
		ObjectPool::Instance()->ClearAll();
		ResourceManager::Instance()->AllRelease();
		ProfilerCPU::Instance()->Clear();
		Tween::mInstance->ClearAll();
		TaskManager::Instance()->ClearAll();

		//NOTE:�d�������H
		BGM::Clear();
		SE::Clear();
	}
}

/**************************************
�V�[���̑��݊m�F
***************************************/
bool SceneManager::ExistsScene(const int sceneID)
{
	return sceneContainer.count(sceneID) != 0;
}

/**************************************
�N���A����
***************************************/
void SceneManager::Clear()
{
	Utility::DeleteMap(sceneContainer);
}
