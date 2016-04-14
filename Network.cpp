#include "Network.h"

static bool instanceFlag = false;
static Network* instance = NULL;

Network::Network()
{
	if (socket.bind(8080) != sf::Socket::Done)
	{
		cout << "Could not bind to specified port" << endl;
	}
	socket.setBlocking(false);
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
	sf::Packet packet;
	IpAddress sender;
	unsigned short port;
	socket.receive(packet, sender, port);
	string message;
	packet >> message;
	cout << "Message Received: " + message << endl;
}

void Network::SendPacket(string message)
{
	sf::Packet packet;
	packet << message;
	IpAddress reciever = "127.0.0.1";
	unsigned short port = 54000;
	socket.send(packet, reciever, port);
	cout << "Sending Message" << endl;
}

void Network::CheckDisconnect(int playerID)
{
}
