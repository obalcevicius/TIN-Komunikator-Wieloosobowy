#include <QtTest>

// add necessary includes here

#include <memory>

#include "nodeinfo.h"
#include "plainmessage.h"
#include "participationmessage.h"


class CommunicationTest : public QObject
{
    Q_OBJECT

public:
    CommunicationTest();
    ~CommunicationTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void participationMessageTest1();

};

CommunicationTest::CommunicationTest()
{

}

CommunicationTest::~CommunicationTest()
{

}

void CommunicationTest::initTestCase()
{

}

void CommunicationTest::cleanupTestCase()
{

}

void CommunicationTest::participationMessageTest1()
{
    NodeInfo nd("127.0.0.1", "2500");
    Communication::ParticipationMessage msg(nd, "subscribe");

    auto p = std::unique_ptr<Communication::PlainMessage>( new Communication::PlainMessage(msg.serialize()));

    Communication::ParticipationMessage after;
    after.deserialize(std::move(p));

    QVERIFY2(after.getNodeInfo().getIPAddress() == "127.0.0.1", "wrong ip address");
    QVERIFY2(after.getNodeInfo().getPort() == "2500", "wrong port");

    QVERIFY2(after.getCommand() == "subscribe", "wrong command");



}

QTEST_APPLESS_MAIN(CommunicationTest)

#include "tst_communicationtest.moc"
