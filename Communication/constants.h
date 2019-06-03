#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace Communication {
/**
 * @brief Class contains definitions for constants
 */
class Constants
{
public:
    static constexpr int incorrectHeader = -1;
    static constexpr int commandMessageHeader = 1;
    static constexpr int participationMessageHeader = 2;

    static constexpr int messageSize = 32;
    static constexpr int headerSize = 34;
    enum class ipVersion {
        IPv4,
        IPv6
    };

private:
    Constants();
};

} // namespace Communication

#endif // CONSTANTS_H
