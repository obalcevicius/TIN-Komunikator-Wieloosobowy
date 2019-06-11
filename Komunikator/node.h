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
    const std::set<NodeInfo>& getGroup(NodeGroup::GroupType) const;
    void setController(Controller* t_controller);
    bool isMember() const;
    bool isSubscriber() const;


signals:

public slots:
    void startServer(unsigned short, Communication::Constants::ipVersion);
    unsigned short getListeningPort() const;
    void setGroup(const std::set<NodeInfo>&, std::string);
    void resetGroup();
    void addNode(const NodeInfo&, std::string);
    void removeNode(const NodeInfo&, std::string);
    void listMembers();
    void broadcastMessage(const Communication::Message&) const;



private:
    void sendMessage(const NodeInfo&, const Communication::Message&);
    void acceptConnections();
    void parseConnection(Communication::Socket t_socket);


    std::unique_ptr<Communication::ServerSocket> m_server;
    std::thread m_acceptingThread;
    Controller* m_controller;
    NodeGroup m_subscribers;
    NodeGroup m_members;
    bool m_isMember;
    bool m_isSubscriber;

};

#endif // NODE_H
