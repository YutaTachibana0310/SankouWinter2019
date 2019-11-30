//=====================================
//
//ObjectPool.h
//�@�\:�I�u�W�F�N�g�v�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ObjectPool : public BaseSingleton<ObjectPool>
{
	friend class SceneManager;
public:
	/**************************************
	�R���X�g���N�^
	***************************************/
	ObjectPool()
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	~ObjectPool()
	{
		ClearAll();
	}

	/**************************************
	�I�u�W�F�N�g�C���X�^���X�쐬����
	���|�C���^��Ԃ��̂ŁA�폜�ɂ��ĕK���Ǘ����邱��
	***************************************/
	template<class T, class ...TArgs>
	T* Create(TArgs... args)
	{
		std::string key = typeid(T).name();
		std::vector<GameObject*>* container = &objectPool[key];

		T* ptr = nullptr;
		
		if (container->empty())
		{
			ptr = new T();
		}
		else
		{
			ptr = dynamic_cast<T*>(container->back());
			container->pop_back();
		}

		return ptr;
	}

	/**************************************
	�I�u�W�F�N�g�C���X�^���X�폜����
	�����ۂɂ͍폜�����v�[�����Ă����A�V�[���J�ڎ��ɍ폜
	***************************************/
	template<class T>
	void Destroy(T* object)
	{
		if (object == nullptr)
			return;

		object->Uninit();

		std::string key = typeid(*object).name();
		objectPool[key].push_back(object);

		object = nullptr;

		return;
	}

private:
	std::unordered_map<std::string, std::vector<GameObject*>> objectPool;

	/**************************************
	�I�u�W�F�N�g�C���X�^���X�������
	***************************************/
	void ClearAll()
	{
		for (auto&& pair : objectPool)
		{
			for (auto&& object : pair.second)
			{
				SAFE_DELETE(object);
			}
			pair.second.clear();
		}
		objectPool.clear();
	}
};
#endif