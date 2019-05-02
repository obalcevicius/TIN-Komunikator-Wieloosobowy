#include "connection.h"

namespace Communication {

Connection::Connection(std::string t_ipAddress, unsigned short t_serverPort, char t_ipVersion) :
    m_socket()
{
    //m_socket.connect(t_ipAddress, t_serverPort);
}

} // namespace Communication
