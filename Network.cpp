#include "Network.h"

static bool instanceFlag = false;
static Network* instance = NULL;

int ThreadedReceive(void* param) {
	static_cast<Network*>(param)->ReceiveMessages();
	return 1;
}

int ThreadedSend(void* param) {
	static_cast<Network*>(param)->SendPacketThread();
	return 0;
}

sf::Packet& operator << (sf::Packet& packet, const NetworkPacket& p)
{
	int size = p.data.size();
	packet << p.type << p.ip << p.playerID << size;
	for (int i = 0; i < size; i++) {
		packet << p.data[i];
	}
	return packet;
}

sf::Packet& operator >> (sf::Packet& packet, NetworkPacket& p)
{
	packet >> p.type >> p.ip >> p.playerID >> p.dataSize;
	int size = p.data.size();
	for (int i = 0; i < size; i++) {
		float dataPiece;
		packet >> dataPiece;
		p.data.push_back(dataPiece);
	}
	return packet;
}

Network::Network()
{
	if (socket.bind(8080) != sf::Socket::Done)
	{
		cout << "Could not bind to specified port" << endl;
	}
	socket.setBlocking(true);

	Parameter p;
	p.param = this;

	ThreadPool::GetInstance()->AddTask(ThreadedReceive, p);
}

Network * Network::GetInstance()
{
	if (!instanceFlag) {
		instance = new Network();
		instanceFlag = true;
	}
	return instance;
}

void Network::Update()
{
	ReceiveMessages();
}

void Network::ReceiveMessages()
{
	cout << "Receiving Message" << endl;
	sf::Packet packet;
	IpAddress sender;
	unsigned short port;
	socket.receive(packet, sender, port);
	NetworkPacket* np = new NetworkPacket();
	packet >> *np;
	receivedPackets.push_back(np);
	HandleMessage();
}

void Network::HandleMessage()
{
	if (receivedPackets.size() > 0) {
		cout << "Handling Message" << endl; 
		for (int i = 0; i < receivedPackets.size(); i++) {
			ProcessMessageData(receivedPackets[i]); 
			delete receivedPackets[i];
			receivedPackets.erase(receivedPackets.begin() + i);
			i--;
		}
	}
}

void Network::ProcessMessageData(NetworkPacket* np)
{
	string messageType;
	unsigned int port = 8080;
	messageType = np->type;
	if (messageType != "NOTHING") {
		if (messageType == "Success") {
			cout << "You connected to the server! :)" << endl;
		}
		else if (messageType == "Start") {
			startGame = true;
		}
	}
}

void Network::SendPacket(IpAddress ip, NetworkPacket* np)
{
	np->ip = IpAddress::getLocalAddress().toString();
	sentMessage = np;

	Parameter p;
	p.param = this;

	ThreadPool::GetInstance()->AddTask(ThreadedSend, p);
}

void Network::SendPacketThread()
{
	sf::Packet packet;
	packet << *sentMessage;
	IpAddress reciever = sentMessage->ip;
	unsigned short port = 54000;
	cout << "Sending Message" << endl;
	socket.send(packet, reciever, port); 
}

void Network::CheckDisconnect(int playerID)
{

}
