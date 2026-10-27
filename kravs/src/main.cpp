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

int main() {
    std::cout << "========================================\n";
    std::cout << "    KRAVS ROBLOX EXECUTOR INITIALIZED   \n";
    std::cout << "    [+]Meezo Tsardom[-]                 \n";
    std::cout << "========================================\n\n";

    // Phase 1: Loading (S1)
    Kravs::Loader loader;
    // For demonstration, verify a placeholder or CMakeLists.txt as a test file
    if (!loader.verifyFile("CMakeLists.txt")) {
        std::cerr << "[FATAL ERROR] S1 Loader: File verification failed.\n";
        return EXIT_FAILURE;
    }
    if (!loader.checkPrivileges("0.600.0")) {
        std::cerr << "[FATAL ERROR] S1 Loader: Privilege check or client version mismatch failed.\n";
        return EXIT_FAILURE;
    }
    if (!loader.prepareBuffer(4096)) {
        std::cerr << "[FATAL ERROR] S1 Loader: Buffer preparation failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 2: Injection (S2)
    Kravs::Injector injector;
    if (!injector.attachProcess(1337)) {
        std::cerr << "[FATAL ERROR] S2 Injector: Process attachment failed.\n";
        return EXIT_FAILURE;
    }
    void* remoteAddr = nullptr;
    if (!injector.allocateAndWriteMemory(loader.getBuffer().data(), loader.getBuffer().size(), remoteAddr)) {
        std::cerr << "[FATAL ERROR] S2 Injector: Memory allocation and write failed.\n";
        return EXIT_FAILURE;
    }
    if (!injector.mapAndExecuteModule(remoteAddr)) {
        std::cerr << "[FATAL ERROR] S2 Injector: Module mapping and execution failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 3: Hooking & Anti-Detection (S3)
    Kravs::HookManager hookMgr;
    if (!hookMgr.installLuauHooks()) {
        std::cerr << "[FATAL ERROR] S3 Hook: Installing Luau hooks failed.\n";
        return EXIT_FAILURE;
    }
    if (!hookMgr.captureThreadCalls()) {
        std::cerr << "[FATAL ERROR] S3 Hook: Capturing thread calls failed.\n";
        return EXIT_FAILURE;
    }
    if (!hookMgr.createTrampolines()) {
        std::cerr << "[FATAL ERROR] S3 Hook: Creating trampolines failed.\n";
        return EXIT_FAILURE;
    }
    if (!hookMgr.hideMemoryModifications()) {
        std::cerr << "[FATAL ERROR] S3 Hook: Hiding memory modifications failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 4: Isolated Environment (S4)
    Kravs::Environment env;
    if (!env.createIsolatedSandbox()) {
        std::cerr << "[FATAL ERROR] S4 Environment: Sandbox creation failed.\n";
        return EXIT_FAILURE;
    }
    if (!env.configureGlobalTables()) {
        std::cerr << "[FATAL ERROR] S4 Environment: Configuring global tables failed.\n";
        return EXIT_FAILURE;
    }
    if (!env.restrictInternalAccess()) {
        std::cerr << "[FATAL ERROR] S4 Environment: Restricting internal access failed.\n";
        return EXIT_FAILURE;
    }
    if (!env.synchronizeClientState()) {
        std::cerr << "[FATAL ERROR] S4 Environment: Client state synchronization failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 5: API Bridge (S5)
    Kravs::ApiBridge bridge;
    if (!bridge.wrapClientFunctions()) {
        std::cerr << "[FATAL ERROR] S5 API Bridge: Wrapping client functions failed.\n";
        return EXIT_FAILURE;
    }
    std::string outType;
    if (bridge.convertTypes("Instance", outType) != 0) {
        std::cerr << "[FATAL ERROR] S5 API Bridge: Type conversion failed.\n";
        return EXIT_FAILURE;
    }
    if (!bridge.validateArguments({"Workspace", "Part"})) {
        std::cerr << "[FATAL ERROR] S5 API Bridge: Argument validation failed.\n";
        return EXIT_FAILURE;
    }
    if (!bridge.queueAsyncCalls([] { std::cout << "[Async Task] Executed via API Bridge queue.\n"; })) {
        std::cerr << "[FATAL ERROR] S5 API Bridge: Queuing async call failed.\n";
        return EXIT_FAILURE;
    }
    if (!bridge.processQueue()) {
        std::cerr << "[FATAL ERROR] S5 API Bridge: Processing async queue failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 6: Scheduler (S6)
    Kravs::Scheduler scheduler;
    if (!scheduler.ingestScript("print('Kravs Executor dynamic pipeline active! 😎')")) {
        std::cerr << "[FATAL ERROR] S6 Scheduler: Script ingestion failed.\n";
        return EXIT_FAILURE;
    }
    if (!scheduler.parseBytecode()) {
        std::cerr << "[FATAL ERROR] S6 Scheduler: Bytecode parsing failed.\n";
        return EXIT_FAILURE;
    }
    if (!scheduler.enqueueTask("MainExecutionTask")) {
        std::cerr << "[FATAL ERROR] S6 Scheduler: Task enqueuing failed.\n";
        return EXIT_FAILURE;
    }
    if (!scheduler.managePriorities()) {
        std::cerr << "[FATAL ERROR] S6 Scheduler: Managing priorities failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 7: Execution Engine (S7) - Dynamic data flow from S6 Scheduler
    Kravs::ExecutionEngine execEngine;
    if (!execEngine.loadBytecodeToVM(scheduler.getCompiledBytecode(), env)) {
        std::cerr << "[FATAL ERROR] S7 Execution: Loading bytecode to VM failed.\n";
        return EXIT_FAILURE;
    }
    if (!execEngine.createContext()) {
        std::cerr << "[FATAL ERROR] S7 Execution: Creating execution context failed.\n";
        return EXIT_FAILURE;
    }
    if (!execEngine.handleErrors()) {
        std::cerr << "[FATAL ERROR] S7 Execution: Error handling setup failed.\n";
        return EXIT_FAILURE;
    }
    // S7 -> S6 feedback loop
    if (!execEngine.returnControlToScheduler(scheduler)) {
        std::cerr << "[FATAL ERROR] S7 Execution: Returning control to scheduler failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 8: UI & Output Management (S8)
    Kravs::UserInterface ui;
    if (!ui.renderConsole()) {
        std::cerr << "[FATAL ERROR] S8 UI: Rendering console failed.\n";
        return EXIT_FAILURE;
    }
    if (!ui.logEvent("Script executed successfully without detection.")) {
        std::cerr << "[FATAL ERROR] S8 UI: Logging event failed.\n";
        return EXIT_FAILURE;
    }
    if (!ui.controlExecution(true)) {
        std::cerr << "[FATAL ERROR] S8 UI: Controlling execution state failed.\n";
        return EXIT_FAILURE;
    }
    ui.updateStatus();

    std::cout << "\n[+] Kravs pipeline execution completed successfully! S9 closing RAII cleanup initiated...\n";
    return EXIT_SUCCESS;
}
