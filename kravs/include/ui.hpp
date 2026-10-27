#ifndef UI_HPP
#define UI_HPP

#include <string>

namespace Kravs {
class UserInterface {
public:
    UserInterface();
    ~UserInterface() = default;

    bool renderConsole();
    bool logEvent(const std::string& message);
    bool controlExecution(bool start);
    bool updateStatus();
};
} // namespace Kravs

#endif // UI_HPP
