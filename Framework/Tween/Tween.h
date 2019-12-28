//=====================================
//
//�g�D�C�[���w�b�_[Transformween.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TWEEN_H_
#define _TWEEN_H_

#include "../../main.h"
#include "../Math/Easing.h"
#include "../Core/Transform.h"
#include "Tweener/ValueTweener.h"

#include <list>
#include <memory>
#include <iterator>
#include <functional>

/**************************************
�O���錾
***************************************/
class BaseTweener;
class Polygon2D;

/**************************************
�}�N���E�񋓎q��`
***************************************/
enum class ExpandType : int
{
	None,
	LeftToRight,
	RightToLeft,
	UpToDown,
	DownToUp,
	ToUpDown,
	ToLeftRight
};

enum class CloseType : int
{
	None,
	LeftToRight,
	RightToLeft,
	UpToDown,
	DownToUp,
	FromUpDown,
	FromLeftRight
};

/**************************************
�N���X��`
***************************************/

class Tween
{
	friend class BaseGame;
	friend class SceneManager;
public:
	/**************************************
	�ړ��g�D�C�[��
	���� ref�F�g�D�C�[���Ώۂ̃Q�[���I�u�W�F�N�g
	���� start : �ړ��J�n���W
	���� end : �ړ�����W
	���� duration : �ړ��ɂ����鎞��
	���� type : �C�[�W���O�^�C�v
	���� callback : �I�����̃R�[���o�b�N�֐�
	***************************************/
	static void Move(GameObject& ref, const D3DXVECTOR3& startPosition, const D3DXVECTOR3& endPosition, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	�ړ��g�D�C�[��
	��{�I�ɂ͏�L�ƈꏏ�����A�ړ��J�n���W�����ݍ��W�Ɏ����Őݒ肵�Ă����
	***************************************/
	static void Move(GameObject& ref, const D3DXVECTOR3& endPosition, int duratino, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	�X�P�[���g�D�C�[��
	���� ref�F�g�D�C�[���Ώۂ̃Q�[���I�u�W�F�N�g
	���� start : �J�n���̃X�P�[��
	���� end : �I�����̃X�P�[��
	���� duration : �X�P�[���ɂ����鎞��
	���� type : �C�[�W���O�^�C�v
	���� callback : �I�����̃R�[���o�b�N�֐�
	***************************************/
	static void Scale(GameObject& ref, const D3DXVECTOR3& startScale, const D3DXVECTOR3& endScale, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	�X�P�[���g�D�C�[��
	��{�I�ɂ͏�L�ƈꏏ�����J�n���̃X�P�[�������݃X�P�[���Ɏ����Őݒ肵�Ă����
	***************************************/
	static void Scale(GameObject& ref, const D3DXVECTOR3& endScale, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	��]�g�D�C�[��
	���� ref�F�g�D�C�[���Ώۂ̃Q�[���I�u�W�F�N�g
	���� start : ��]�J�n�p�x�i�I�C���[�p�j
	���� end : ��]�I���p�x�i�I�C���[�p�j
	���� duration : ��]�ɂ����鎞��
	���� type : �C�[�W���O�^�C�v
	���� callback : �I�����̃R�[���o�b�N�֐�
	����]�p�x�͎�����0.0f~360.0f�ɕ␳����Ă��܂��̂Œ���
	***************************************/
	static void Rotate(GameObject& ref, const D3DXVECTOR3& startEulerAngle, const D3DXVECTOR3& endEulerAngle, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	��]�g�D�C�[��
	��{�I�ɂ͏�L�ƈꏏ�����J�n�̉�]�p�x�������Ō��݊p�x�ɐݒ肵�Ă����
	***************************************/
	static void Rotate(GameObject& ref, const D3DXVECTOR3& endEulaerAngle, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	�����g�D�C�[��
	���� ref�F�g�D�C�[���Ώۂ̃Q�[���I�u�W�F�N�g
	���� endDirection : ��]�I�����̑O����
	���� duration : ��]�ɂ����鎞��
	���� type : �C�[�W���O�^�C�v
	���� dummyAxis : �n�_�̌����ƏI�_�̌��������s�������ꍇ�Ɏg�p�����]��
	���� callback : �I�����̃R�[���o�b�N�֐�
	***************************************/
	static void Turn(GameObject& ref, const D3DXVECTOR3& endDirection, int duration, EaseType type, const D3DXVECTOR3& dummyAxis, std::function<void()> callback = nullptr);

	/**************************************
	�l�g�D�C�[��
	���� ref�F�g�D�C�[���Ώۂ̕ϐ��ւ̃X�}�[�g�|�C���^
	���� start : �J�n���̒l
	���� end : �I�����̒l
	���� duration : �ω��ɂ����鎞��
	���� type : �C�[�W���O�^�C�v
	���� callback : �I�����̃R�[���o�b�N�֐�
	***************************************/
	template<class T>
	static void To(std::shared_ptr<T>& ref, const T& start, const T& end, int duration, EaseType type, std::function<void()> callback = nullptr)
	{
		ValueTweener<T> *tweener = new ValueTweener<T>(ref, start, end, duration, type, callback);
		mInstance->tweenerContainer.push_back(tweener);
	}

	/**************************************
	�l�g�D�C�[��
	���� ref�F�g�D�C�[���Ώۂ̕ϐ��ւ̃X�}�[�g�|�C���^
	���� end : �I�����̒l
	���� duration : �ω��ɂ����鎞��
	���� type : �C�[�W���O�^�C�v
	���� callback : �I�����̃R�[���o�b�N�֐�
	***************************************/
	template<class T>
	static void To(std::shared_ptr<T>& ref, const T& end, int duration, EaseType type, std::function<void()> callback = nullptr)
	{
		T start = *ref;
		ValueTweener<T> *tweener = new ValueTweener<T>(ref, start, end, duration, type, callback);
		mInstance->tweenerContainer.push_back(tweener);
	}

	static void Expand(std::shared_ptr<Polygon2D>& ref, ExpandType expand, int duration, EaseType type, std::function<void()> callback = nullptr);

	static void Close(std::shared_ptr<Polygon2D>& ref, CloseType close, int duration, EaseType type, std::function<void()> callback = nullptr);

	static void Fade(std::shared_ptr<Polygon2D>& ref, float start, float end, int duration, EaseType type, std::function<void()> callback = nullptr);

private:
	void Update();
	void ClearContainer();
	void ClearAll();

	std::list<BaseTweener*> tweenerContainer;

	static Tween* mInstance;
	Tween();
	~Tween();
};

#endif