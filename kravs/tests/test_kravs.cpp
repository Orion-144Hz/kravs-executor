#include <iostream>
#include <cstdlib>
#include "loader.hpp"
#include "injector.hpp"
#include "hook.hpp"
#include "environment.hpp"
#include "api_bridge.hpp"
#include "scheduler.hpp"
#include "execution.hpp"
#include "ui.hpp"

#define KRAVS_TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "[TEST FAILURE] " << #condition << " failed: " << message << "\n"; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

void testLoader() {
    std::cout << "[Test] Running Loader positive & negative tests...\n";
    Kravs::Loader loader;
    KRAVS_TEST_ASSERT(loader.verifyFile("CMakeLists.txt") == true, "Valid file verification failed");
    KRAVS_TEST_ASSERT(loader.checkPrivileges("0.600.0") == true, "Valid version check failed");
    KRAVS_TEST_ASSERT(loader.prepareBuffer(1024) == true, "Buffer preparation failed");
    KRAVS_TEST_ASSERT(loader.getBuffer().size() == 1024, "Buffer size mismatch");

    // Negative tests for S1 Loader
    KRAVS_TEST_ASSERT(loader.verifyFile("non_existent_file_12345.dll") == false, "Negative test: non-existent file should fail");
    KRAVS_TEST_ASSERT(loader.checkPrivileges("invalid_version") == false, "Negative test: invalid version should fail");
    std::cout << "[Test] Loader tests passed! ✅\n";
}

void testInjector() {
    std::cout << "[Test] Running Injector positive & negative tests...\n";
    Kravs::Injector injector;
    KRAVS_TEST_ASSERT(injector.attachProcess(1337) == true, "Valid process attachment failed");
    void* addr = nullptr;
    uint8_t data[64] = {0x90};
    KRAVS_TEST_ASSERT(injector.allocateAndWriteMemory(data, sizeof(data), addr) == true, "Memory allocation & write failed");
    KRAVS_TEST_ASSERT(injector.mapAndExecuteModule(addr) == true, "Module mapping failed");

    // Negative tests for S2 Injector
    Kravs::Injector negInjector;
    KRAVS_TEST_ASSERT(negInjector.attachProcess(0) == false, "Negative test: PID 0 attachment must be rejected");
    void* nullAddr = nullptr;
    KRAVS_TEST_ASSERT(negInjector.allocateAndWriteMemory(nullptr, 64, nullAddr) == false, "Negative test: nullptr data must fail allocation");
    std::cout << "[Test] Injector tests passed! ✅\n";
}

void testHook() {
    std::cout << "[Test] Running Hook tests...\n";
    Kravs::HookManager hook;
    KRAVS_TEST_ASSERT(hook.installLuauHooks() == true, "Install Luau hooks failed");
    KRAVS_TEST_ASSERT(hook.captureThreadCalls() == true, "Capture thread calls failed");
    KRAVS_TEST_ASSERT(hook.createTrampolines() == true, "Create trampolines failed");
    KRAVS_TEST_ASSERT(hook.hideMemoryModifications() == true, "Hide memory modifications failed");
    KRAVS_TEST_ASSERT(hook.unhook() == true, "Unhook cleanup failed");
    std::cout << "[Test] Hook tests passed! ✅\n";
}

void testEnvironment() {
    std::cout << "[Test] Running Environment tests...\n";
    Kravs::Environment env;
    KRAVS_TEST_ASSERT(env.createIsolatedSandbox() == true, "Create sandbox failed");
    KRAVS_TEST_ASSERT(env.configureGlobalTables() == true, "Configure global tables failed");
    KRAVS_TEST_ASSERT(env.restrictInternalAccess() == true, "Restrict internal access failed");
    KRAVS_TEST_ASSERT(env.synchronizeClientState() == true, "Synchronize client state failed");
    KRAVS_TEST_ASSERT(env.destroyState() == true, "Destroy state failed");
    std::cout << "[Test] Environment tests passed! ✅\n";
}

void testApiBridge() {
    std::cout << "[Test] Running API Bridge tests...\n";
    Kravs::ApiBridge bridge;
    KRAVS_TEST_ASSERT(bridge.wrapClientFunctions() == true, "Wrap client functions failed");
    std::string outType;
    KRAVS_TEST_ASSERT(bridge.convertTypes("Part", outType) == 0, "Type conversion failed");
    KRAVS_TEST_ASSERT(outType == "lua_Part", "Converted type mismatch");
    KRAVS_TEST_ASSERT(bridge.validateArguments({"Workspace", "Part"}) == true, "Argument validation failed");
    KRAVS_TEST_ASSERT(bridge.queueAsyncCalls([] {}) == true, "Queue async call failed");
    KRAVS_TEST_ASSERT(bridge.processQueue() == true, "Process queue failed");

    // Negative tests for S5 API Bridge
    std::string dummyOut;
    KRAVS_TEST_ASSERT(bridge.convertTypes("", dummyOut) != 0, "Negative test: empty type conversion should fail");
    KRAVS_TEST_ASSERT(bridge.validateArguments({"INVALID"}) == false, "Negative test: invalid argument should fail");
    std::cout << "[Test] API Bridge tests passed! ✅\n";
}

void testScheduler() {
    std::cout << "[Test] Running Scheduler positive & negative tests...\n";
    Kravs::Scheduler scheduler;
    KRAVS_TEST_ASSERT(scheduler.ingestScript("print('test script')") == true, "Ingest script failed");
    KRAVS_TEST_ASSERT(scheduler.parseBytecode() == true, "Parse bytecode failed");
    KRAVS_TEST_ASSERT(scheduler.enqueueTask("Task1") == true, "Enqueue task failed");
    KRAVS_TEST_ASSERT(scheduler.managePriorities() == true, "Manage priorities failed");

    // Negative tests for S6 Scheduler
    KRAVS_TEST_ASSERT(scheduler.ingestScript("") == false, "Negative test: empty script ingestion must fail");
    std::cout << "[Test] Scheduler tests passed! ✅\n";
}

void testExecution() {
    std::cout << "[Test] Running Execution tests...\n";
    Kravs::Environment env;
    env.createIsolatedSandbox();
    Kravs::Scheduler scheduler;
    scheduler.ingestScript("print('exec test')");
    scheduler.parseBytecode();

    Kravs::ExecutionEngine exec;
    KRAVS_TEST_ASSERT(exec.loadBytecodeToVM(scheduler.getCompiledBytecode(), env) == true, "Load bytecode to VM failed");
    KRAVS_TEST_ASSERT(exec.createContext() == true, "Create execution context failed");
    KRAVS_TEST_ASSERT(exec.handleErrors() == true, "Handle errors failed");
    KRAVS_TEST_ASSERT(exec.returnControlToScheduler(scheduler) == true, "Return control to scheduler failed");

    // Negative tests for S7 Execution
    Kravs::ExecutionEngine negExec;
    Kravs::Environment emptyEnv;
    std::vector<uint8_t> emptyBytecode;
    KRAVS_TEST_ASSERT(negExec.loadBytecodeToVM(emptyBytecode, emptyEnv) == false, "Negative test: empty bytecode loading must fail");
    std::cout << "[Test] Execution tests passed! ✅\n";
}

void testUI() {
    std::cout << "[Test] Running UI tests...\n";
    Kravs::UserInterface ui;
    KRAVS_TEST_ASSERT(ui.renderConsole() == true, "Render console failed");
    KRAVS_TEST_ASSERT(ui.logEvent("test log") == true, "Log event failed");
    KRAVS_TEST_ASSERT(ui.controlExecution(true) == true, "Control execution failed");
    KRAVS_TEST_ASSERT(ui.updateStatus() == "Active / Executing", "Status telemetry mismatch");
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

    std::cout << "\n[+] All Kravs unit and negative tests passed successfully! 🚀😎\n";
    return 0;
}
