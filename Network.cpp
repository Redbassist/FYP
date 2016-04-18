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
	int size = p.dataSize;
	for (int i = 0; i < size; i++) {
		float dataPiece;
		packet >> dataPiece;
		p.data.push_back(dataPiece);
	}
	return packet;
}

Network::Network()
{
	if (sendSocket.bind(80) != sf::Socket::Done)
	{
		cout << "Could not bind to specified port" << endl;
	}
	sendSocket.setBlocking(true);

	if (receiveSocket.bind(8080) != sf::Socket::Done)
	{
		cout << "Could not bind to specified port" << endl;
	}
	receiveSocket.setBlocking(true);

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
	//cout << "Receiving Message" << endl;
	sf::Packet packet;
	IpAddress sender;
	unsigned short port;
	receiveSocket.receive(packet, sender, port);
	NetworkPacket* np = new NetworkPacket();
	packet >> *np;
	receivedPackets.push_back(np);
	HandleMessage();
}

void Network::HandleMessage()
{
	if (receivedPackets.size() > 0) {
		//cout << "Handling Message" << endl; 
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
		else if (messageType == "EnemyPlayerData") {
			int numberPlayersSent = np->dataSize / 22;  

			mutexR.lock();

			for (int i = 0; i < numberPlayersSent; i++) {
				int size = players.size();
				bool foundPlayer = false;
				for (int j = 0; j < size; j++) {
					if (players[j].id == (int)np->data[22 * i]) {
						players[j].update = true;
						players[j].data.clear();
						vector<float>::const_iterator begin = np->data.begin() + (22 * i);
						vector<float>::const_iterator end = np->data.begin() + (22 * (i + 1));
						players[j].data = vector<float>(begin, end);
						foundPlayer = true;
						break;
					}
				}
				if (!foundPlayer) {
					PlayerInfo temp;
					temp.id = (int)np->data[22 * i];
					temp.update = true;
					vector<float>::const_iterator begin = np->data.begin() + (22 * i);
					vector<float>::const_iterator end = np->data.begin() + (22 * (i + 1));
					temp.data = vector<float>(begin, end);
					players.push_back(temp);
				}
			}

			mutexR.unlock();
		}
	}
}

void Network::SendPacket(IpAddress ip, NetworkPacket* np)
{
	np->ip = IpAddress::getLocalAddress().toString();
	sentMessages.push_back(np);

	Parameter p;
	p.param = this;

	ThreadPool::GetInstance()->AddTask(ThreadedSend, p);
}

void Network::SendPacketThread()
{
	sf::Packet packet;
	if (sentMessages.size() > 0) {
		packet << *sentMessages[0];
		IpAddress reciever = "192.168.1.8";
		unsigned short port = 54000;
		//cout << "Sending Message" << endl;
		sendSocket.send(packet, reciever, port);
		delete sentMessages[0];
		sentMessages.erase(sentMessages.begin());
	}
}

void Network::CheckDisconnect(int playerID)
{

}
