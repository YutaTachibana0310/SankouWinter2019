//=============================================================================
//
// ���������[�N�����N���X [MemoryDetect.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _MemoryDetect_H_
#define _MemoryDetect_H_


// ���������[�N�����p
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

// new�̃I�[�o�[���[�h
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif