#include "ui.hpp"
#include <iostream>

namespace Kravs {
UserInterface::UserInterface() : isRunning_(false), eventCount_(0) {}

bool UserInterface::renderConsole() {
    std::cout << "[S8] Rendering Kravs Console & Script Editor Interface...\n";
    return true;
}

bool UserInterface::logEvent(const std::string& message) {
    if (message.empty()) {
        std::cerr << "[S8 ERROR] Cannot log empty message.\n";
        return false;
    }
    eventCount_++;
    std::cout << "[S8 LOG #" << eventCount_ << "] " << message << "\n";
    return true;
}

bool UserInterface::controlExecution(bool start) {
    isRunning_ = start;
    std::cout << "[S8] Execution control state updated: " << (isRunning_ ? "RUNNING" : "STOPPED") << "\n";
    return true;
}

std::string UserInterface::updateStatus() const {
    std::string status = isRunning_ ? "Active / Executing" : "Idle / Ready";
    std::cout << "[S8] Status Telemetry: " << status << " (Events logged: " << eventCount_ << ")\n";
    return status;
}
} // namespace Kravs
