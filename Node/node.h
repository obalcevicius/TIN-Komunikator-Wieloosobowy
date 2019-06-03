#ifndef NODE_H
#define NODE_H

#include <future>
#include <mutex>
#include <string>
#include <thread>

#include "constants.h"
#include "clientsocket.h"
#include "message.h"
#include "messagevisitor.h"
#include "nodegroup.h"
#include "nodeinfo.h"
#include "serversocket.h"


class Node
{
public:
    Node(Communication::Constants::ipVersion t_ipVersion, std::string t_ipAddress, std::string t_port);

    bool broadcastMessage(const Communication::Message& t_message) const;
    void joinGroup(std::string t_ipAddress, std::string t_port);
    void startListening();
    void stopListening();

private:
    void acceptConnections(bool& t_finish);
    void parseConnection(Communication::Socket t_socket);
    void sendMessage(const NodeInfo& t_node, const Communication::Message& t_msg, std::promise<bool>&& t_return ) const ;
    std::thread m_acceptingThread;
    mutable NodeGroup m_subscribers;
    mutable NodeGroup m_members;
    NodeInfo m_thisNode;
    Communication::ServerSocket m_server;
    bool m_isListening;
};

#endif // NODE_H
