//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include <process.h>
#include "UDPClient.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
HANDLE UDPClient::Thread = 0;
SOCKET UDPClient::ClientSocket = 0;
sockaddr_in UDPClient::ServerAddress;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPClient::UDPClient()
{
	// WinSock������
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// �\�P�b�g����
	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ���M��A�h���X
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = inet_addr("255.255.255.255");//�u���[�h�L���X�g�A�h���X

	// �u���[�h�L���X�g����
	int value = 1;
	setsockopt(ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value));

	// �N���C�A���g��M�X���b�h�J�n
	Thread = (HANDLE)_beginthreadex(NULL, 0, ThreadEntryPoint, this, 0, NULL);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPClient::~UDPClient()
{
	ThreadStop = true;

	// WinSock�I������
	closesocket(ClientSocket);
	WSACleanup();

	// ===============================================================
	// ���ӁB������ƃX���b�h�I���֐�(_endthreadex)���Ă΂Ȃ���
	// ���C���X���b�h���I��������ɑ��̃X���b�h�͂��̂܂܎��s���܂�
	// ��O�X���[�̉\��������
	// ===============================================================
	// �X���b�h���������܂ő҂�
	DWORD ThreadResult = WaitForSingleObject(Thread, INFINITE);
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// �X���b�h�I��
		CloseHandle(Thread);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UDPClient::Update(void)
{
	if (!InLoading)
		return;
}

//=============================================================================
// �`�揈��
//=============================================================================
void UDPClient::Draw(void)
{
	if (!InLoading)
		return;
}

//=============================================================================
// �����L���O�ǉ��p�P�b�g���M
//=============================================================================
void UDPClient::SendRankPacket(string NameStr, string AILevel)
{
	string Message;

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::InsertRank) + "," + NameStr + "," + AILevel;

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �����L���O�ǉ��p�P�b�g���M
//=============================================================================
void UDPClient::SendRankPacket(string NameStr, unsigned long long AILevel)
{
	string AILevelStr = std::to_string(AILevel);
	SendRankPacket(NameStr, AILevelStr);
}

//=============================================================================
// �C�x���g���p�p�P�b�g���M
//=============================================================================
void UDPClient::SendEventPacket(string EventNo, string FieldLevel)
{
	string Message;

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::EventLive) + "," + EventNo + "," + FieldLevel;

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �C�x���g���p�p�P�b�g���M
//=============================================================================
void UDPClient::SendEventPacket(int EventNo, int FieldLevel)
{
	string EventNoStr = std::to_string(EventNo);
	string FieldLevelStr = std::to_string(FieldLevel);
	SendEventPacket(EventNoStr, FieldLevelStr);
}

//=============================================================================
// �t�B�[���h���x���A�b�v�p�P�b�g���M
//=============================================================================
void UDPClient::SendLevelUpPacket(void)
{
	string Message;

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::LevelUp);

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �Z�J���h�X���b�h
//=============================================================================
unsigned __stdcall UDPClient::ThreadEntryPoint(void* This)
{
	UDPClient* Temp = (UDPClient*)This;
	Temp->GetScorePacket();					// �{���̃Z�J���h�X���b�h�̏����֐�
	_endthreadex(0);						// �X���b�h�̎��s��~
	return 0;
}

//=============================================================================
// �T�[�o�[���烉���L���O�ŉ��ʂ̃X�R�A���擾
//=============================================================================
void UDPClient::GetScorePacket(void)
{
	// �f�[�^���M
	char data[256];
	string Message;
	int AddressLength;

	AddressLength = sizeof(ServerAddress);

	while (!ThreadStop)
	{
		memset(data, 0, sizeof(data));

		// ���b�Z�[�W��M
		recvfrom(ClientSocket, (char*)data, sizeof(data), 0, (sockaddr*)&ServerAddress, &AddressLength);

		// �f�[�^����
		Message = data;
		if (!Message.empty())
		{
			LastScore = std::stoull(Message);
			ReceiveSuccess = true;
		}
	}
}

//=============================================================================
// ���N�G�X�g
//=============================================================================
void UDPClient::TryGetLastScore(void)
{
	// �f�[�^���M
	string Message;
	int AddressLength;

	AddressLength = sizeof(ServerAddress);

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::GetLastScore);

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, AddressLength);
}

//=============================================================================
// �C�x���g���p�p�P�b�g���M
//=============================================================================
unsigned long long UDPClient::GetLastScore(void)
{
	ReceiveSuccess = false;
	InLoading = true;
	TimeoutCount = 0;

	// �X���b�h�܂��������Ȃ��̂ŁA������x�T�[�o�[�Ƀ��N�G�X�g
	TryGetLastScore();

	while (TimeoutCount <= 60)
	{
		DWORD Result = WaitForSingleObject(Thread, 1);

		// �X���b�h����I��
		if (ReceiveSuccess)
		{
			break;
		}
		// �^�C���A�E�g
		else
		{
			TimeoutCount++;

			// ���N�G�X�g
			if (TimeoutCount % 3 == 0)
				TryGetLastScore();
		}
	}

	if (ReceiveSuccess)
	{
		return LastScore;
	}
	else
	{
		return 0;
	}
}
