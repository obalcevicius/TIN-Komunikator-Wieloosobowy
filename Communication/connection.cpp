#include "connection.h"

namespace Communication {

Connection::Connection(std::string t_serverAddress, std::string t_serverPort, char t_ipVersion) :
    m_socket()
{

    m_socket.connect(t_serverAddress, t_serverPort);
}





} // namespace Communication
