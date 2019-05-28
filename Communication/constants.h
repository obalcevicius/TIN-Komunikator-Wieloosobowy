#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace Communication {
/**
 * @brief Class contains definitions for constants
 */
class Constants
{
public:
    static constexpr int commandMessageHeader = 1;
    enum class ipVersion {
        IPv4,
        IPv6
    };

private:
    Constants();
};

} // namespace Communication

#endif // CONSTANTS_H
