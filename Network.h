#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include "stdafx.h" 
#include "Globals.h"

using namespace std;
using namespace sf;

struct NetworkPacket {
	string type = "NOTHING";
	string ip;
	int playerID = 0;
	int dataSize = 0;
	vector<float> data;
};

struct PlayerInfo {
	int id = 0;
	bool update = false;
	vector<float> data;
};

class Network {
private:
	vector<pair<IpAddress, unsigned short>> connectedPlayerInfo;
	vector<PlayerInfo> players;
	UdpSocket socket;
	vector<NetworkPacket*> receivedPackets;
	NetworkPacket* sentMessage;
public:
	Network();
	static Network* GetInstance();
	void Update();
	void ReceiveMessages();
	void HandleMessage();
	void ProcessMessageData(NetworkPacket*);
	void SendPacket(IpAddress, NetworkPacket*);
	void SendPacketThread();
	void CheckDisconnect(int playerID);
	vector<PlayerInfo> GetPlayerData() { return players; }
	bool startGame = false;
};

#endif