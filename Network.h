#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include "stdafx.h" 
#include "Globals.h"

using namespace std;
using namespace sf;

struct NetworkPacket {
	string type = "NOTHING";
	int playerID = 0;
};

class Network {
private:
	vector<pair<string, int>> ConnectPlayerInfo;
	UdpSocket socket;
public:
	Network();
	static Network* GetInstance();
	void Update();
	void ReceiveMessages();
	void SendPacket(string message);
	void CheckDisconnect(int playerID);
};

#endif