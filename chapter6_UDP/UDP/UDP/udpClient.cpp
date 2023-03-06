#include "udpClient.h"
// UDP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <string>

#pragma comment(lib,"Ws2_32.lib")
#pragma warning(disable : 4996)

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
std::string msg;
int recvLen;
char result[30];
int serverAddrLen;
int udpInit()
{

	int ret;
	ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0) {
		std::cout << "WSAStartup failed" << std::endl;
		return 1;
	}

	//socket creat

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cout << "socket creat failed" << std::endl;
		return 1;
	}


	// 设置超时
	u_long argp = 1;
	ioctlsocket(sock, FIONBIO, &argp);

	//send

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//inet_addr被弃用
	//serverAddr.sin_addr.s_addr = inet_addr("192.168.147.129");
	//新用法
	//ret = InetPton(AF_INET, TEXT("192.168.147.129"), &serverAddr.sin_addr.s_addr);
	//如果是广播
	ret = InetPton(AF_INET, TEXT("255.255.255.255"), &serverAddr.sin_addr.s_addr);
	/*if (sock != 1) {
		std::cout << "InetPton failed" << std::endl;
		return 1;
	}*/
	serverAddr.sin_port = htons(9190);
	//设置是否广播
	int broadEnable = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadEnable, sizeof(broadEnable));

	memset(&result, 0, sizeof(result));
	serverAddrLen = sizeof(serverAddr);
	msg = "IP";

}

void udpDeinit()
{
	closesocket(sock);
	WSACleanup();
}

int getIp(char* ip)
{
	std::cout << "socket start" << std::endl;
	sendto(sock, msg.c_str(), msg.size(), 0, (SOCKADDR*)&serverAddr, serverAddrLen);
	Sleep(500);
	recvLen = recvfrom(sock, result, 30, 0, (SOCKADDR*)&serverAddr, &serverAddrLen);
	if (recvLen != -1) {
		result[recvLen] = 0;
	}

	std::cout << "recv: " << result << std::endl;
	if (recvLen == 16) {
		strcpy(ip, result);
		return 1;
	}
	return 0;
}
