#include "Nfc.h"
#include "Main.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

#define PORT 9999		//ポート番号
#define IP "127.0.0.1"	//IP番号(ローカルホスト) 

void strReplace(std::string& str, const std::string& from, const std::string& to);

void Nfc::Init() 
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
}

char* Nfc::GetId()
{
	if (CheckHitKey(KEY_INPUT_S)) //Sキー（スキップ）が押されたら
		return "daichi";
	if (!NFC_FLAG) //NFC_FLAGがfalseだったら
		return "\0";

	//接続に失敗したときのエラー処理
	//またnfc監視を初めてから1秒間の間は0を返す
	calledCont++;
	if (!Connect(IP, PORT) || calledCont < 10) {
		return "\0";
	}

	int recvsize;					//受信データ長
	char recvMessage[5] = {"\0"};	//受信バッファ
	char data[256] = { "\0" };		//受信したIDを格納する変数
	char* p1 = data;				//実際にreturnするデータ

	//受信
	//tcp/ip通信では4バイトごと送信される
	//つまり一回受信しただけでは完全に受信されていない可能性がある
	//なので何度か受信されたか確認することによって完全に受信させる
	while (true) {
		RECVSTATUS status = Recv(
			recvMessage,		//受信データ格納用の配列 
			sizeof(recvsize),	//受信データ長
			&recvsize);			//受信データ長のポインタ

		switch (status) {
		//データが来ていないとき
		case RECV_STILL:
			continue;
		//成功
		case RECV_SUCCESSED:
			strcat_s(data, sizeof(data), recvMessage);
			for (int i = 0; i < 5; i++) {
				recvMessage[i] = '\0';
			}
			continue;
		//切断orエラー
		case RECV_FAILED:
			break;
		}

		break;
	}

	//制御文字の削除
	//処理を減らすためにデータがあるときのみ調べる
	if (data[0] != '\0') {
		//文字列がナルになるか配列の範囲内でループ
		//確認されている制御文字はstx(0x02),\r(0x0a),\n(0x0d)
		for (int i = 0; *(p1 + i) == '\0' || i < 256; i++) {
			//まずstxの削除をする
			//これは文頭につくのでアドレスを1つインクリメントする
			if (*(p1 + i) == 0x02) {
				p1++;
			}
			//残り二つを削除
			//これは文末につくのでナルで上書きする
			if (*(p1 + i) == 0x0a || *(p1 + i) == 0x0d)  {
				*(p1 + i) = '\0';
			}
		}
	}

	return p1;
}

//接続
bool Nfc::Connect(const char* Ip, u_short Port)
{
	//sockaddr_in 構造体のセット
	struct sockaddr_in dstAddr;
	memset(&dstAddr, 0, sizeof(dstAddr));
	dstAddr.sin_port = htons(Port);
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_addr.s_addr = inet_addr(Ip);

	//ソケットの生成
	m_DstSocket = socket(AF_INET, SOCK_STREAM, 0);

	//接続
	if (connect(m_DstSocket, (struct sockaddr *) & dstAddr, sizeof(dstAddr))
		== SOCKET_ERROR) {
		return false;
	}
	//ソケットを非同期モードにする
	u_long val = 1;
	ioctlsocket(m_DstSocket, FIONBIO, &val);
	return true;
}

//受信
RECVSTATUS Nfc::Recv(char* pData, int DataSize, int *pRecvSize) 
{
	int n = recv(m_DstSocket, pData, DataSize, 0);
	if (n < 1) {
		//データが来ていない
		if (WSAGetLastError() == WSAEWOULDBLOCK) {
			return RECV_STILL;
		//切断orエラー
		} else {
			return RECV_FAILED;
		}
	}
	*pRecvSize = n;	//受信データ長取得
	return RECV_SUCCESSED;
}

void Nfc::reset_calledCont() { calledCont = 0; }

/**
* 文字列中から文字列を検索して別の文字列に置換する
* @param str  : 置換対象の文字列。上書かれます。
* @param from : 検索文字列
* @param to   : 置換後の文字列
*/
void strReplace(std::string& str, const std::string& from, const std::string& to) {
	std::string::size_type pos = 0;
	while (pos = str.find(from, pos), pos != std::string::npos) {
		str.replace(pos, from.length(), to);
		pos += to.length();
	}
}