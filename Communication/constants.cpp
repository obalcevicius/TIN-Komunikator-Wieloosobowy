#include <arpa/inet.h>

#include "constants.h"

namespace Communication {

Constants::Constants()
{

}

bool Constants::isIPv4Address(const std::string& t_address) {

    char address4_[INET_ADDRSTRLEN];
    return inet_pton(AF_INET, t_address.c_str(), address4_) != 0;


}
bool Constants::isIPv6Address(const std::string& t_address) {
    char address6_[INET6_ADDRSTRLEN];
    return inet_pton(AF_INET6, t_address.c_str(), address6_) != 0;

}





} // namespace Communication
