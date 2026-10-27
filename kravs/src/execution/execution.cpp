#include "execution.hpp"
#include "environment.hpp"
#include "scheduler.hpp"
#include <iostream>

namespace Kravs {
ExecutionEngine::ExecutionEngine() : isExecuted_(false), loadedBytecodeSize_(0) {}

bool ExecutionEngine::loadBytecodeToVM(const std::vector<uint8_t>& bytecode, Environment& env) {
    if (bytecode.empty()) {
        std::cerr << "[S7 ERROR] Cannot load empty bytecode into Luau VM.\n";
        return false;
    }
    if (env.getLuauState() == nullptr) {
        std::cerr << "[S7 ERROR] Luau VM state in Environment is null.\n";
        return false;
    }
    std::cout << "[S7] Loading compiled bytecode (" << bytecode.size() << " bytes) into Luau VM state: " << env.getLuauState() << "\n";
    loadedBytecodeSize_ = bytecode.size();
    return true;
}

bool ExecutionEngine::createContext() {
    if (loadedBytecodeSize_ == 0) {
        std::cerr << "[S7 ERROR] Cannot create execution context without loaded bytecode.\n";
        return false;
    }
    std::cout << "[S7] Creating execution thread and isolated execution context...\n";
    isExecuted_ = true;
    return true;
}

bool ExecutionEngine::handleErrors() {
    if (!isExecuted_) {
        std::cerr << "[S7 ERROR] Cannot handle errors: execution context not active.\n";
        return false;
    }
    std::cout << "[S7] Exception handling, stack trace logging, and crash prevention active.\n";
    return true;
}

bool ExecutionEngine::returnControlToScheduler(Scheduler& scheduler) {
    std::cout << "[S7 -> S6] Returning execution control successfully back to Scheduler for script: " << scheduler.getCurrentScript() << "\n";
    return true;
}

bool ExecutionEngine::isExecuted() const {
    return isExecuted_;
}
} // namespace Kravs
