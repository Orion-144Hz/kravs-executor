#include <iostream>
#include <cassert>
#include "loader.hpp"
#include "injector.hpp"
#include "hook.hpp"
#include "environment.hpp"
#include "api_bridge.hpp"
#include "scheduler.hpp"
#include "execution.hpp"
#include "ui.hpp"

void testLoader() {
    std::cout << "[Test] Running Loader tests...\n";
    Kravs::Loader loader;
    assert(loader.verifyFile("test.dll") == true);
    assert(loader.checkPrivileges() == true);
    assert(loader.prepareBuffer(1024) == true);
    assert(loader.getBuffer().size() == 1024);
    std::cout << "[Test] Loader tests passed! ✅\n";
}

void testInjector() {
    std::cout << "[Test] Running Injector tests...\n";
    Kravs::Injector injector;
    assert(injector.attachProcess(1234) == true);
    void* addr = nullptr;
    uint8_t data[64] = {0};
    assert(injector.allocateAndWriteMemory(data, sizeof(data), addr) == true);
    assert(injector.mapAndExecuteModule(addr) == true);
    std::cout << "[Test] Injector tests passed! ✅\n";
}

void testHook() {
    std::cout << "[Test] Running Hook tests...\n";
    Kravs::HookManager hook;
    assert(hook.installLuauHooks() == true);
    assert(hook.captureThreadCalls() == true);
    assert(hook.createTrampolines() == true);
    assert(hook.hideMemoryModifications() == true);
    std::cout << "[Test] Hook tests passed! ✅\n";
}

void testEnvironment() {
    std::cout << "[Test] Running Environment tests...\n";
    Kravs::Environment env;
    assert(env.createIsolatedSandbox() == true);
    assert(env.configureGlobalTables() == true);
    assert(env.restrictInternalAccess() == true);
    assert(env.synchronizeClientState() == true);
    std::cout << "[Test] Environment tests passed! ✅\n";
}

void testApiBridge() {
    std::cout << "[Test] Running API Bridge tests...\n";
    Kravs::ApiBridge bridge;
    assert(bridge.wrapClientFunctions() == true);
    assert(bridge.convertTypes() == true);
    assert(bridge.validateArguments() == true);
    assert(bridge.queueAsyncCalls() == true);
    std::cout << "[Test] API Bridge tests passed! ✅\n";
}

void testScheduler() {
    std::cout << "[Test] Running Scheduler tests...\n";
    Kravs::Scheduler scheduler;
    assert(scheduler.ingestScript("print('hello')") == true);
    assert(scheduler.parseBytecode() == true);
    assert(scheduler.enqueueTask("Task1") == true);
    assert(scheduler.managePriorities() == true);
    std::cout << "[Test] Scheduler tests passed! ✅\n";
}

void testExecution() {
    std::cout << "[Test] Running Execution tests...\n";
    Kravs::ExecutionEngine exec;
    assert(exec.loadBytecodeToVM("bytecode") == true);
    assert(exec.createContext() == true);
    assert(exec.handleErrors() == true);
    assert(exec.returnControlToScheduler() == true);
    std::cout << "[Test] Execution tests passed! ✅\n";
}

void testUI() {
    std::cout << "[Test] Running UI tests...\n";
    Kravs::UserInterface ui;
    assert(ui.renderConsole() == true);
    assert(ui.logEvent("test log") == true);
    assert(ui.controlExecution(true) == true);
    assert(ui.updateStatus() == true);
    std::cout << "[Test] UI tests passed! ✅\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "    KRAVS EXECUTOR UNIT TEST SUITE      \n";
    std::cout << "    [+]Meezo Tsardom[-]                 \n";
    std::cout << "========================================\n\n";

    testLoader();
    testInjector();
    testHook();
    testEnvironment();
    testApiBridge();
    testScheduler();
    testExecution();
    testUI();

    std::cout << "\n[+] All Kravs unit tests passed successfully! 🚀😎\n";
    return 0;
}
