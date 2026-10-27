#include "ui.hpp"
#include <iostream>

namespace Kravs {
UserInterface::UserInterface() = default;

bool UserInterface::renderConsole() {
    std::cout << "[S8] Rendering Kravs Executor console & script editor UI...\n";
    return true;
}

bool UserInterface::logEvent(const std::string& message) {
    std::cout << "[S8 LOG] " << message << "\n";
    return true;
}

bool UserInterface::controlExecution(bool start) {
    std::cout << "[S8] Execution control -> " << (start ? "STARTED" : "STOPPED") << "\n";
    return true;
}

bool UserInterface::updateStatus() {
    std::cout << "[S8] Status updated: Ready / Idle\n";
    return true;
}
} // namespace Kravs
