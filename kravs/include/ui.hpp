#ifndef UI_HPP
#define UI_HPP

#include <string>

namespace Kravs {
class ExecutionEngine;

class UserInterface {
public:
    UserInterface(ExecutionEngine& executionEngine);
    ~UserInterface() = default;

    bool renderConsole();
    bool logEvent(const std::string& message);
    bool controlExecution(bool start);
    bool updateStatus(std::string& outStatus) const;

private:
    ExecutionEngine& executionEngine_;
    bool isRunning_;
    size_t eventCount_;
};
} // namespace Kravs

#endif // UI_HPP
