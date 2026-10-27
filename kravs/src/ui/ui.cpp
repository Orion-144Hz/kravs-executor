#include "ui.hpp"
#include "execution.hpp"
#include <iostream>

namespace Kravs {
UserInterface::UserInterface(ExecutionEngine& executionEngine) 
    : executionEngine_(executionEngine), isRunning_(false), eventCount_(0) {}

bool UserInterface::renderConsole() {
    std::cout << "[S8] Rendering Kravs Console & Script Editor Interface...\n";
    return true;
}

bool UserInterface::logEvent(const std::string& message) {
    if (message.empty()) {
        std::cerr << "[S8 ERROR [Code 801]] Cannot log empty message.\n";
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

bool UserInterface::updateStatus(std::string& outStatus) const {
    bool execActive = executionEngine_.isExecuted();
    if (isRunning_ != execActive) {
        std::cerr << "[S8 WARNING] UI running state out of sync with ExecutionEngine state.\n";
    }
    outStatus = isRunning_ ? "Active / Executing (Engine Ready)" : "Idle / Ready (Engine Standby)";
    std::cout << "[S8] Status Telemetry: " << outStatus << " | Events Logged: " << eventCount_ << "\n";
    return true; // Returns status success code
}
} // namespace Kravs
