//=============================================================================
//
// UDP�T�[�o�[�N���X [UDPServer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _UDPServer_H_
#define _UDPServer_H_

#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServer
{
private:
	SOCKET ServerSocket;

	void ReceivePacket(void);

#if _DEBUG
	std::vector<sockaddr_in> ConnectedList;
#endif

public:
	UDPServer();
	~UDPServer();

	// �}���`�X���b�h�p
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
};

#endif
