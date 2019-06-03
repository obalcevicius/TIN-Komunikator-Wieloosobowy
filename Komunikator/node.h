#ifndef NODE_H
#define NODE_H

#include <QObject>

#include <memory>
#include <future>
#include <set>
#include <string>
#include <vector>

#include "controller.h"
#include "nodeinfo.h"
#include "nodegroup.h"
#include "serversocket.h"

class Node : public QObject
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = nullptr);
    void startListening();
    void joinGroup(std::string t_ipAddress, std::string t_port);
    bool isMember(const NodeInfo&);
    bool isSubscriber(const NodeInfo&);


signals:

public slots:
    void startServer(unsigned short, Communication::Constants::ipVersion);
    void setGroup(const std::set<NodeInfo>&, const std::string&);
    void addNode(const NodeInfo&, const std::string&);
    void removeNode(const NodeInfo&, const std::string&);
    void broadcastMessage(const Communication::Message&) const;



private:
    void sendMessage(const NodeInfo&, const Communication::Message&);
    void acceptConnections();
    void parseConnection(Communication::Socket t_socket);


    std::unique_ptr<Communication::ServerSocket> m_server;
    std::thread m_acceptingThread;
    Controller* m_controller;
    mutable NodeGroup m_subscribers;
    mutable NodeGroup m_members;
};

#endif // NODE_H
