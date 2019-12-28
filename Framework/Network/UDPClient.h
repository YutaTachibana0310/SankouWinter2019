//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _UDPClient_H_
#define _UDPClient_H_

#include <string>
#include "PacketConfig.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPClient
{
private:
	static SOCKET ClientSocket;
	static sockaddr_in ServerAddress;
	int TimeoutCount = 0;
	bool InLoading = false;
	bool ReceiveSuccess = false;
	bool ThreadStop = false;
	unsigned long long LastScore = 0;

	void TryGetLastScore(void);
	void GetScorePacket(void);

	// �}���`�X���b�h�p	
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);

public:
	UDPClient();
	~UDPClient();
	void Update(void);
	void Draw(void);
	static void SendRankPacket(std::string NameStr, std::string AILevel);
	static void SendRankPacket(std::string NameStr, unsigned long long AILevel);
	static void SendEventPacket(std::string EventNo, std::string FieldLevel);
	static void SendEventPacket(int EventNo, int FieldLevel);
	static void SendLevelUpPacket(void);
	unsigned long long GetLastScore(void);
};

#endif
