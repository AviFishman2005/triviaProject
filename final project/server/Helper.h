#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>
#include <bitset>
#include <iostream>

enum MessageType : char
{
	MT_LOG_IN = '2',
	MT_SIGN_UP = '3',
	MT_LOGOUT = '5',
	MT_ERROR = '4',
	MT_CROOM = '6',
	MT_JROOM = '7',
	MT_PROOM = '8',
	MT_STATS = '9',
	MT_GROOM = 'a',
	MT_HSCORE = 'b',
	MT_CLOSE_ROOM = 'c',
	MT_SGAME = 's',
	MT_GSTATE = 'g',
	MT_LROOM = 'l',
	MT_CLIENT_UPDATE = 204,
	MT_CLIENT_FINISH = 207,
	MT_CLIENT_EXIT = 208,
	MT_SERVER_UPDATE = 101,
};
enum F_SERVER : int
{
	OK = 1,
	FAIL = 2,
};

#define HEXADECIMAL_255 0xff
#define BYTE_SIZE 8
class Helper
{
public:


	static int getMessageTypeCode(const SOCKET sc);
	static std::string toBinary(int n);
	static std::vector<unsigned char>toBinarySerialize(MessageType m, const std::vector<unsigned char>& message);

	static int getIntPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getStringPartFromSocket(SOCKET sc, const int bytesNum);
	static void sendData(const SOCKET sc, const std::string message);
	static void send_update_message_to_client(const SOCKET sc, const std::string& file_content, const std::string& second_username, const std::string& all_users);
	static std::string getPaddedNumber(const int num, const int digits);

private:
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags);

};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif