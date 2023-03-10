// UDP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#include "udpClient.h"

#pragma comment(lib,"Ws2_32.lib")

#pragma warning(disable : 4996)

int main()
{
#if 0
    //std::cout << "Hello World!\n";
    //WSAStartup
    WSADATA wsaData;
    int ret;
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0) {
        std::cout << "WSAStartup failed" << std::endl;
        return 1;
    }

    //socket creat
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cout << "socket creat failed" << std::endl;
        return 1;
    }


    // 设置超时
    u_long argp = 1;
    ioctlsocket(sock, FIONBIO, &argp);

    //send
    SOCKADDR_IN serverAddr;
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
    std::string msg;
    int recvLen;
    char result[30];
    memset(&result, 0, sizeof(result));
    int serverAddrLen = sizeof(serverAddr);
    while (true)
    {
        std::cout << "socket start" << std::endl;
        while (std::getline(std::cin, msg))
        {
            sendto(sock, msg.c_str(), msg.size(), 0, (SOCKADDR*)&serverAddr, serverAddrLen);
            Sleep(500);
            recvLen = recvfrom(sock, result, 30, 0, (SOCKADDR*)&serverAddr, &serverAddrLen);
            if (recvLen != -1) {
                result[recvLen] = 0;
            }
            std::cout << "recv: " << result << std::endl;
            msg.clear();
        }
    }
    closesocket(sock);
    WSACleanup();
#endif
    char result[30];
    udpInit();
    getIp(result);
    std::cout << "result: " << result << std::endl;
    udpDeinit();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
