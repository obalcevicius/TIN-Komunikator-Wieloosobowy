#ifndef NODE_H
#define NODE_H

#include <string>
#include <thread>

#include "constants.h"
#include "clientsocket.h"
#include "message.h"
#include "nodegroup.h"
#include "nodeinfo.h"
#include "serversocket.h"


class Node
{
public:
    Node(Communication::Constants::ipVersion t_ipVersion, std::string t_ipAddress, std::string t_port);

    //void broadcastMessage(const Communication::Message& t_message);
    void broadcastMessage(const Communication::PlainMessage& t_msg);
    void joinGroup(std::string t_ipAddress, std::string t_port);
    void startListening();
    void stopListening();

private:
    void acceptConnections(bool& t_finish);
    bool m_isListening;
    std::thread m_acceptingThread;
    NodeGroup m_subscribers;
    NodeGroup m_members;
    NodeInfo m_thisNode;
    Communication::ServerSocket m_server;
};

#endif // NODE_H
