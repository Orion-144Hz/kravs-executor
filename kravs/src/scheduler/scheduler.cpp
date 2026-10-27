#include "scheduler.hpp"
#include <iostream>

namespace Kravs {
Scheduler::Scheduler() : isCancelled_(false) {}

bool Scheduler::ingestScript(const std::string& script) {
    if (script.empty()) {
        std::cerr << "[S6 ERROR] Cannot ingest empty script.\n";
        return false;
    }
    std::cout << "[S6] Ingesting script (length: " << script.length() << " chars)...\n";
    currentScript_ = script;
    isCancelled_ = false;
    return true;
}

bool Scheduler::parseBytecode() {
    if (currentScript_.empty()) {
        std::cerr << "[S6 ERROR] No script ingested to parse into bytecode.\n";
        return false;
    }
    std::cout << "[S6] Parsing script and compiling to Luau bytecode...\n";
    // Simulate compilation of currentScript_ into bytecode vector
    compiledBytecode_.clear();
    for (char c : currentScript_) {
        compiledBytecode_.push_back(static_cast<uint8_t>(c ^ 0x5A)); // Dummy bytecode transform
    }
    compiledBytecode_.push_back(0x1B); // Luau bytecode header magic proxy
    std::cout << "[S6] Bytecode compilation successful. Compiled size: " << compiledBytecode_.size() << " bytes.\n";
    return true;
}

bool Scheduler::enqueueTask(const std::string& taskName) {
    if (taskName.empty()) {
        std::cerr << "[S6 ERROR] Cannot enqueue empty task name.\n";
        return false;
    }
    std::cout << "[S6] Enqueuing task: " << taskName << "\n";
    taskQueue_.push(taskName);
    return true;
}

bool Scheduler::managePriorities() {
    std::cout << "[S6] Managing task execution priorities in queue (pending tasks: " << taskQueue_.size() << ")...\n";
    return true;
}

bool Scheduler::cancelTask(const std::string& taskName) {
    std::cout << "[S6] Cancelling task execution: " << taskName << "\n";
    isCancelled_ = true;
    return true;
}

bool Scheduler::rerunTask(const std::string& taskName) {
    std::cout << "[S6] Rerunning task execution: " << taskName << "\n";
    isCancelled_ = false;
    return true;
}

const std::vector<uint8_t>& Scheduler::getCompiledBytecode() const {
    return compiledBytecode_;
}

const std::string& Scheduler::getCurrentScript() const {
    return currentScript_;
}
} // namespace Kravs
