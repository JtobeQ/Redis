// RedisL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "redis/hiredis.h"
#include <string>
#include <iostream>
#include <functional>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"hiredis.lib")

auto foo(int i, int j)->decltype(i+j)
{
	return  i + j;
}


int _tmain(int argc, _TCHAR* argv[])
{

	//初始化ws2_32库
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 1), &wsaData);
	int timeout = 10000;
	struct timeval tv;
	tv.tv_sec = timeout / 1000;
	tv.tv_usec = timeout * 1000;

	std::string ip = "127.0.0.1";
	auto port = 6379;

	auto context = redisConnect(ip.c_str(), port);

	if (context == nullptr)
	{
		std::cout << "connect null!";
		return 0;
	}

	if (context->err)
	{
		std::cout << "connect error!";
		return 0;
	}


	auto reply = (redisReply*)redisCommand(context, "get citys");

	if (!reply || reply->str == nullptr|| reply->type != REDIS_REPLY_STRING)
	{
		std::cout << "command error!";
		freeReplyObject(reply); 
		redisFree(context); 
		getchar();
		return  0;
	}

	std::cout << reply->str;
	freeReplyObject(reply);

	redisFree(context);


	getchar();

	return 0;
}

