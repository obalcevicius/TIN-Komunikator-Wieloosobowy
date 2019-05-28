#ifndef NODE_H
#define NODE_H

#include <string>
#include "constants.h"
#include "message.h"
#include "nodegroup.h"
#include "nodeinfo.h"
#include "serversocket.h"


class Node
{
public:
    Node(Communication::Constants::ipVersion t_ipVersion, std::string t_ipAddress, std::string t_port);
    void acceptConnection(); //todo: start a new thread
    void broadcastMessage(const Communication::Message& t_message);
    void startListening();

private:
    NodeGroup m_subscribers;
    NodeGroup m_members;
    NodeInfo m_thisNode;
    Communication::ServerSocket m_server;
};

#endif // NODE_H