//=====================================
//
//�g�����X�t�H�[���w�b�_[Transform.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../main.h"
#include "../Math/Quaternion.h"

#include <list>
#include <memory>

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Transform
{
public:
	//�R���X�g���N�^
	Transform();
	Transform(const Transform&);
	virtual ~Transform() {}

	//���Z�q
	virtual Transform operator = (const Transform&);

	//�ړ�����
	virtual void Move(const D3DXVECTOR3& velocity);

	virtual void SetPosition(const D3DXVECTOR3& position);
	virtual void SetLocalPosition(const D3DXVECTOR3& position);

	virtual D3DXVECTOR3 GetPosition() const;
	virtual D3DXVECTOR3 GetLocalPosition() const;

	//��]����
	virtual void Rotate(float degreeX, float degreeY, float degreeZ);
	virtual void Rotate(float degree, const D3DXVECTOR3& axis);
	virtual void Rotate(const D3DXQUATERNION& quaternion);

	virtual void SetRotation(const D3DXVECTOR3& rotation);
	virtual void SetRotation(const D3DXQUATERNION& rotation);
	virtual void SetLocalRotation(const D3DXVECTOR3& rotation);
	virtual void SetLocalRotation(const D3DXQUATERNION& rotation);

	virtual D3DXVECTOR3 GetEulerAngle() const;
	virtual D3DXVECTOR3 GetLocalEulerAngle() const;

	virtual D3DXQUATERNION GetRotation() const;
	virtual D3DXQUATERNION GetLocalRotation() const;

	//�X�P�[������
	virtual void Scale(const D3DXVECTOR3& delta);

	virtual void SetScale(const D3DXVECTOR3& scale);
	virtual void SetLocalScale(const D3DXVECTOR3& scale);

	virtual D3DXVECTOR3 GetScale() const;
	virtual D3DXVECTOR3 GetLocalScale() const;

	//����
	virtual D3DXVECTOR3 Forward() const;
	virtual D3DXVECTOR3 Right() const;
	virtual D3DXVECTOR3 Up() const;

	//���[���h�ϊ��ݒ菈��
	virtual void SetWorld() const;
	virtual D3DXMATRIX GetMatrix() const;

	//�w��̈ʒu���������鏈��
	void LookAt(const D3DXVECTOR3& target);

	//�e�q�ݒ�
	virtual void AddChild(const std::shared_ptr<Transform>& transform);
	virtual void RemoveChild(Transform* transform);
	
protected:
	D3DXMATRIX mtxWorldGlobal;		//�O���[�o����Ԃł̕ϊ��s��
	D3DXVECTOR3 position;			//���W
	D3DXVECTOR3 scale;				//�X�P�[��
	D3DXQUATERNION rotation;		//��]

	D3DXMATRIX mtxWorldLocal;		//���[�J����Ԃł̕ϊ��s��
	D3DXVECTOR3 localPosition;		//���[�J�����W
	D3DXVECTOR3 localScale;			//���[�J���X�P�[��
	D3DXQUATERNION localRotation;	//���[�J����]

	void OnUpdateParentMatrix(const D3DXMATRIX& mtxWorld);

	void MoveMatrix(const D3DXVECTOR3& offset);
	void RotateMatrix(const D3DXQUATERNION& rotate);
	void ScaleMatrix(const D3DXVECTOR3& scale);

	void _SetScale(const D3DXVECTOR3& scale);

	void UpdateChildMatrix();

	std::list<std::weak_ptr<Transform>> listChildren;
};

#endif