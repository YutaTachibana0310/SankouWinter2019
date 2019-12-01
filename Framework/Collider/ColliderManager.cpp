//=====================================
//
//�R���C�_�[�}�l�[�W������[ColliderManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ColliderManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�Փ˔��菈��
***************************************/
void ColliderManager::Update()
{
	//�Q�ƕs�\�ȃ|�C���^���폜
	for (auto&& pair : boxColliderMap)
	{
		pair.second.remove_if([](std::weak_ptr<BoxCollider3D> ptr)
		{
			return ptr.expired();
		});
	}
}

/**************************************
�N���A����
***************************************/
void ColliderManager::Clear()
{
	for (auto&& pair : boxColliderMap)
	{
		pair.second.clear();
	}
	boxColliderMap.clear();
}

/**************************************
�w�肵���^�O�̃R���C�_�[���m�ő������蔻��
***************************************/
void ColliderManager::CheckRoundRobin(const std::string & tag1, const std::string & tag2)
{
	//NOTE : ���̊֐��̑O�ŎQ�ƕs�\�ȃ|�C���^�͍폜���Ă���̂ŁA�����E�����N�؂�͋C�ɂ��Ȃ�

	//���݂��Ȃ��^�O�̏ꍇ�͑������^�[��
	if (boxColliderMap.count(tag1) == 0 || boxColliderMap.count(tag2) == 0)
		return;

	for (auto&& ptr1 : boxColliderMap[tag1])
	{
		//�A�N�e�B�u�łȂ��R���C�_�[��continue
		std::shared_ptr<BoxCollider3D> collider1 = ptr1.lock();
		if (!collider1->IsActive())
			continue;

		for (auto&& ptr2 : boxColliderMap[tag2])
		{
			//�A�N�e�B�u�łȂ��R���C�_�[��continue
			std::shared_ptr<BoxCollider3D> collider2 = ptr2.lock();
			if (!collider2->IsActive())
				continue;

			//�������g�Ƃ̔���͍s��Ȃ�
			if (collider1 == collider2)
				continue;

			//�Փ˔���
			collider1->CheckCollision(*collider2);
		}
	}
}

/**************************************
�{�b�N�X�R���C�_�[�ǉ�����
***************************************/
void ColliderManager::AddBoxCollider3D(const std::string & tag, std::shared_ptr<BoxCollider3D>& entity)
{
	std::weak_ptr<BoxCollider3D> ptr = std::weak_ptr<BoxCollider3D>(entity);
	boxColliderMap[tag].push_back(ptr);
}


