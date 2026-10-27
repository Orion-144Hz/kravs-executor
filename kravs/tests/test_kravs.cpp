#include <iostream>
#include <cstdlib>
#include <cstring>
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
    KRAVS_TEST_ASSERT(loader.checkPrivileges("0.600.0") == true, "Valid semantic version check failed");
    KRAVS_TEST_ASSERT(loader.prepareBuffer(1024) == true, "Buffer preparation failed");
    KRAVS_TEST_ASSERT(loader.getBuffer().size() == 1024, "Buffer size mismatch");

    // Negative tests for S1 Loader
    KRAVS_TEST_ASSERT(loader.verifyFile("non_existent_file_12345.dll") == false, "Negative test: non-existent file should fail [Code 404]");
    KRAVS_TEST_ASSERT(loader.checkPrivileges("invalid_version") == false, "Negative test: invalid version format should fail [Code 401]");
    std::cout << "[Test] Loader tests passed! ✅\n";
}

void testInjector() {
    std::cout << "[Test] Running Injector positive & negative tests (isolated)...\n";
    
    // Positive test
    Kravs::Injector injector;
    KRAVS_TEST_ASSERT(injector.attachProcess(1337) == true, "Valid process attachment failed");
    void* addr = nullptr;
    uint8_t data[64] = {0x90};
    KRAVS_TEST_ASSERT(injector.allocateAndWriteMemory(data, sizeof(data), addr) == true, "Memory allocation & write failed");
    KRAVS_TEST_ASSERT(injector.mapAndExecuteModule(addr) == true, "Module mapping failed");

    // Negative test 1: PID 0
    Kravs::Injector negInjector1;
    KRAVS_TEST_ASSERT(negInjector1.attachProcess(0) == false, "Negative test: PID 0 attachment must be rejected [Code 501]");

    // Negative test 2: Nullptr data with valid handle
    Kravs::Injector negInjector2;
    negInjector2.attachProcess(1337);
    void* nullAddr = nullptr;
    KRAVS_TEST_ASSERT(negInjector2.allocateAndWriteMemory(nullptr, 64, nullAddr) == false, "Negative test: nullptr data must fail allocation [Code 503]");

    // Negative test 3: 0-byte size with valid handle
    Kravs::Injector negInjector3;
    negInjector3.attachProcess(1337);
    void* zeroAddr = nullptr;
    KRAVS_TEST_ASSERT(negInjector3.allocateAndWriteMemory(data, 0, zeroAddr) == false, "Negative test: 0-byte size allocation must be rejected [Code 504]");

    // Negative test 4: Simulated WriteProcessMemory failure
    Kravs::Injector negInjector4;
    negInjector4.attachProcess(1337);
    negInjector4.setSimulateWriteFailure(true);
    void* failAddr = nullptr;
    KRAVS_TEST_ASSERT(negInjector4.allocateAndWriteMemory(data, sizeof(data), failAddr) == false, "Negative test: simulated write failure must return false [Code 506]");

    std::cout << "[Test] Injector tests passed! ✅\n";
}

void testHook() {
    std::cout << "[Test] Running HookManager tests (with real table & detach/unhide)...\n";
    Kravs::HookManager hook;
    KRAVS_TEST_ASSERT(hook.installLuauHooks() == true, "Install Luau hooks failed");
    KRAVS_TEST_ASSERT(hook.captureThreadCalls() == true, "Capture thread calls failed");
    KRAVS_TEST_ASSERT(hook.createTrampolines() == true, "Create trampolines failed");
    KRAVS_TEST_ASSERT(hook.hideMemoryModifications() == true, "Hide memory modifications failed");
    KRAVS_TEST_ASSERT(hook.isStealthActive() == true, "Stealth flag should be active");
    KRAVS_TEST_ASSERT(hook.unhide() == true, "Unhide failed");
    KRAVS_TEST_ASSERT(hook.detach() == true, "Detach failed");
    KRAVS_TEST_ASSERT(hook.unhook() == true, "Unhook cleanup failed");
    std::cout << "[Test] Hook tests passed! ✅\n";
}

void testEnvironment() {
    std::cout << "[Test] Running Environment tests (Luau state)...\n";
    Kravs::Environment env;
    KRAVS_TEST_ASSERT(env.createIsolatedSandbox() == true, "Create sandbox failed");
    KRAVS_TEST_ASSERT(env.getLuauState() != nullptr, "Luau state pointer must not be null");
    KRAVS_TEST_ASSERT(env.configureGlobalTables() == true, "Configure global tables failed");
    KRAVS_TEST_ASSERT(env.restrictInternalAccess() == true, "Restrict internal access failed");
    KRAVS_TEST_ASSERT(env.synchronizeClientState() == true, "Synchronize client state failed");
    KRAVS_TEST_ASSERT(env.destroyState() == true, "Destroy state failed");
    std::cout << "[Test] Environment tests passed! ✅\n";
}

void testApiBridge() {
    std::cout << "[Test] Running API Bridge positive & negative tests...\n";
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
    KRAVS_TEST_ASSERT(scheduler.cancelTask("Task1") == true, "Cancel task failed");
    KRAVS_TEST_ASSERT(scheduler.rerunTask("Task1") == true, "Rerun task failed");

    // Negative tests for S6 Scheduler
    KRAVS_TEST_ASSERT(scheduler.ingestScript("") == false, "Negative test: empty script ingestion must fail");
    std::cout << "[Test] Scheduler tests passed! ✅\n";
}

void testExecution() {
    std::cout << "[Test] Running Execution positive & negative tests (isolated)...\n";
    Kravs::Environment env;
    env.createIsolatedSandbox();
    Kravs::Scheduler scheduler;
    scheduler.ingestScript("print('exec test')");
    scheduler.parseBytecode();

    // Positive test
    Kravs::ExecutionEngine exec;
    KRAVS_TEST_ASSERT(exec.loadBytecodeToVM(scheduler.getCompiledBytecode(), env) == true, "Load bytecode to VM failed");
    KRAVS_TEST_ASSERT(exec.createContext() == true, "Create execution context failed");
    KRAVS_TEST_ASSERT(exec.handleErrors() == true, "Handle errors failed");
    KRAVS_TEST_ASSERT(exec.returnControlToScheduler(scheduler) == true, "Return control to scheduler failed");

    // Negative test 1: Empty bytecode with valid VM state
    Kravs::ExecutionEngine negExec1;
    std::vector<uint8_t> emptyBytecode;
    KRAVS_TEST_ASSERT(negExec1.loadBytecodeToVM(emptyBytecode, env) == false, "Negative test: empty bytecode loading must fail");

    // Negative test 2: Valid bytecode with null VM state
    Kravs::ExecutionEngine negExec2;
    Kravs::Environment nullEnv; // not initialized
    KRAVS_TEST_ASSERT(negExec2.loadBytecodeToVM(scheduler.getCompiledBytecode(), nullEnv) == false, "Negative test: null VM state loading must fail");

    std::cout << "[Test] Execution tests passed! ✅\n";
}

void testUI() {
    std::cout << "[Test] Running UI & Telemetry binding tests...\n";
    Kravs::ExecutionEngine exec;
    Kravs::UserInterface ui(exec);
    KRAVS_TEST_ASSERT(ui.renderConsole() == true, "Render console failed");
    KRAVS_TEST_ASSERT(ui.logEvent("test log") == true, "Log event failed");
    KRAVS_TEST_ASSERT(ui.controlExecution(true) == true, "Control execution failed");
    
    std::string statusStr;
    KRAVS_TEST_ASSERT(ui.updateStatus(statusStr) == true, "Update status should return true/success code");
    KRAVS_TEST_ASSERT(!statusStr.empty(), "Status string telemetry must not be empty");
    std::cout << "[Test] UI tests passed! ✅\n";
}

int main(int argc, char* argv[]) {
    std::cout << "========================================\n";
    std::cout << "    KRAVS EXECUTOR COMMIT 1b TEST SUITE \n";
    std::cout << "    [+]Meezo Tsardom[-]                 \n";
    std::cout << "========================================\n\n";

    if (argc > 1) {
        std::string testGroup = argv[1];
        if (testGroup == "LoaderTest") { testLoader(); }
        else if (testGroup == "InjectorTest") { testInjector(); }
        else if (testGroup == "HookTest") { testHook(); }
        else if (testGroup == "EnvTest") { testEnvironment(); }
        else if (testGroup == "BridgeTest") { testApiBridge(); }
        else if (testGroup == "SchedulerTest") { testScheduler(); }
        else if (testGroup == "ExecutionTest") { testExecution(); }
        else if (testGroup == "UITest") { testUI(); }
        else {
            std::cerr << "Unknown test group: " << testGroup << "\n";
            return EXIT_FAILURE;
        }
    } else {
        testLoader();
        testInjector();
        testHook();
        testEnvironment();
        testApiBridge();
        testScheduler();
        testExecution();
        testUI();
    }

    std::cout << "\n[+] All Commit 1b unit and negative tests passed successfully! 🚀😎\n";
    return 0;
}
