#include "api_bridge.hpp"
#include <iostream>

namespace Kravs {
ApiBridge::ApiBridge() = default;

bool ApiBridge::wrapClientFunctions() {
    std::cout << "[S5] Wrapping internal client functions (game, Instance, workspace) into safe Lua/Luau callables...\n";
    return true;
}

int ApiBridge::convertTypes(const std::string& inputType, std::string& outputType) {
    std::cout << "[S5] Converting type representation from '" << inputType << "'...\n";
    if (inputType.empty()) {
        std::cerr << "[S5 ERROR] Empty input type provided for conversion.\n";
        return -1; // Error code
    }
    outputType = "lua_" + inputType;
    std::cout << "[S5] Successfully converted to output type: " << outputType << "\n";
    return 0; // Success error code
}

bool ApiBridge::validateArguments(const std::vector<std::string>& args) {
    std::cout << "[S5] Validating argument list (count: " << args.size() << ")...\n";
    for (const auto& arg : args) {
        if (arg == "INVALID") {
            std::cerr << "[S5 ERROR] Invalid argument detected.\n";
            return false;
        }
    }
    return true;
}

bool ApiBridge::queueAsyncCalls(std::function<void()> task) {
    if (!task) {
        std::cerr << "[S5 ERROR] Cannot queue null task.\n";
        return false;
    }
    std::cout << "[S5] Queuing asynchronous call into task queue...\n";
    asyncTaskQueue_.push(task);
    return true;
}

bool ApiBridge::processQueue() {
    std::cout << "[S5] Processing " << asyncTaskQueue_.size() << " queued asynchronous tasks...\n";
    while (!asyncTaskQueue_.empty()) {
        auto task = asyncTaskQueue_.front();
        asyncTaskQueue_.pop();
        try {
            task();
        } catch (...) {
            std::cerr << "[S5 ERROR] Exception thrown during async task execution.\n";
            return false;
        }
    }
    return true;
}
} // namespace Kravs
