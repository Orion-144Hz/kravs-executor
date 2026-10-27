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
    std::cout << "    KRAVS ROBLOX EXECUTOR COMMIT 1b     \n";
    std::cout << "    [+]Meezo Tsardom[-]                 \n";
    std::cout << "========================================\n\n";

    // Phase 1: Loading (S1)
    Kravs::Loader loader;
    if (!loader.verifyFile("CMakeLists.txt")) {
        std::cerr << "[FATAL ERROR [Code 404]] Stage S1 (Loader::verifyFile) failed.\n";
        return EXIT_FAILURE;
    }
    if (!loader.checkPrivileges("0.600.0")) {
        std::cerr << "[FATAL ERROR [Code 401]] Stage S1 (Loader::checkPrivileges) failed.\n";
        return EXIT_FAILURE;
    }
    if (!loader.prepareBuffer(4096)) {
        std::cerr << "[FATAL ERROR [Code 422]] Stage S1 (Loader::prepareBuffer) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 2: Injection (S2)
    Kravs::Injector injector;
    if (!injector.attachProcess(1337)) {
        std::cerr << "[FATAL ERROR [Code 502]] Stage S2 (Injector::attachProcess) failed.\n";
        return EXIT_FAILURE;
    }
    void* remoteAddr = nullptr;
    if (!injector.allocateAndWriteMemory(loader.getBuffer().data(), loader.getBuffer().size(), remoteAddr)) {
        std::cerr << "[FATAL ERROR [Code 508]] Stage S2 (Injector::allocateAndWriteMemory) failed.\n";
        return EXIT_FAILURE;
    }
    if (!injector.mapAndExecuteModule(remoteAddr)) {
        std::cerr << "[FATAL ERROR [Code 509]] Stage S2 (Injector::mapAndExecuteModule) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 3: Hooking & Anti-Detection (S3)
    Kravs::HookManager hookMgr;
    if (!hookMgr.installLuauHooks()) {
        std::cerr << "[FATAL ERROR [Code 601]] Stage S3 (HookManager::installLuauHooks) failed.\n";
        return EXIT_FAILURE;
    }
    if (!hookMgr.captureThreadCalls()) {
        std::cerr << "[FATAL ERROR [Code 602]] Stage S3 (HookManager::captureThreadCalls) failed.\n";
        return EXIT_FAILURE;
    }
    if (!hookMgr.createTrampolines()) {
        std::cerr << "[FATAL ERROR [Code 603]] Stage S3 (HookManager::createTrampolines) failed.\n";
        return EXIT_FAILURE;
    }
    if (!hookMgr.hideMemoryModifications()) {
        std::cerr << "[FATAL ERROR [Code 604]] Stage S3 (HookManager::hideMemoryModifications) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 4: Isolated Environment (S4)
    Kravs::Environment env;
    if (!env.createIsolatedSandbox()) {
        std::cerr << "[FATAL ERROR [Code 701]] Stage S4 (Environment::createIsolatedSandbox) failed.\n";
        return EXIT_FAILURE;
    }
    if (!env.configureGlobalTables()) {
        std::cerr << "[FATAL ERROR [Code 702]] Stage S4 (Environment::configureGlobalTables) failed.\n";
        return EXIT_FAILURE;
    }
    if (!env.restrictInternalAccess()) {
        std::cerr << "[FATAL ERROR [Code 703]] Stage S4 (Environment::restrictInternalAccess) failed.\n";
        return EXIT_FAILURE;
    }
    if (!env.synchronizeClientState()) {
        std::cerr << "[FATAL ERROR [Code 704]] Stage S4 (Environment::synchronizeClientState) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 5: API Bridge (S5)
    Kravs::ApiBridge bridge;
    if (!bridge.wrapClientFunctions()) {
        std::cerr << "[FATAL ERROR [Code 801]] Stage S5 (ApiBridge::wrapClientFunctions) failed.\n";
        return EXIT_FAILURE;
    }
    std::string outType;
    if (bridge.convertTypes("Instance", outType) != 0) {
        std::cerr << "[FATAL ERROR [Code 802]] Stage S5 (ApiBridge::convertTypes) failed.\n";
        return EXIT_FAILURE;
    }
    if (!bridge.validateArguments({"Workspace", "Part"})) {
        std::cerr << "[FATAL ERROR [Code 803]] Stage S5 (ApiBridge::validateArguments) failed.\n";
        return EXIT_FAILURE;
    }
    if (!bridge.queueAsyncCalls([] { std::cout << "[Async Task] Executed via API Bridge queue.\n"; })) {
        std::cerr << "[FATAL ERROR [Code 804]] Stage S5 (ApiBridge::queueAsyncCalls) failed.\n";
        return EXIT_FAILURE;
    }
    if (!bridge.processQueue()) {
        std::cerr << "[FATAL ERROR [Code 805]] Stage S5 (ApiBridge::processQueue) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 6: Scheduler (S6)
    Kravs::Scheduler scheduler;
    if (!scheduler.ingestScript("print('Kravs Executor Commit 1b dynamic pipeline active! 😎')")) {
        std::cerr << "[FATAL ERROR [Code 901]] Stage S6 (Scheduler::ingestScript) failed.\n";
        return EXIT_FAILURE;
    }
    if (!scheduler.parseBytecode()) {
        std::cerr << "[FATAL ERROR [Code 902]] Stage S6 (Scheduler::parseBytecode) failed.\n";
        return EXIT_FAILURE;
    }
    if (!scheduler.enqueueTask("MainExecutionTask")) {
        std::cerr << "[FATAL ERROR [Code 903]] Stage S6 (Scheduler::enqueueTask) failed.\n";
        return EXIT_FAILURE;
    }
    if (!scheduler.managePriorities()) {
        std::cerr << "[FATAL ERROR [Code 904]] Stage S6 (Scheduler::managePriorities) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 7: Execution Engine (S7)
    Kravs::ExecutionEngine execEngine;
    if (!execEngine.loadBytecodeToVM(scheduler.getCompiledBytecode(), env)) {
        std::cerr << "[FATAL ERROR [Code 1001]] Stage S7 (ExecutionEngine::loadBytecodeToVM) failed.\n";
        return EXIT_FAILURE;
    }
    if (!execEngine.createContext()) {
        std::cerr << "[FATAL ERROR [Code 1002]] Stage S7 (ExecutionEngine::createContext) failed.\n";
        return EXIT_FAILURE;
    }
    if (!execEngine.handleErrors()) {
        std::cerr << "[FATAL ERROR [Code 1003]] Stage S7 (ExecutionEngine::handleErrors) failed.\n";
        return EXIT_FAILURE;
    }
    if (!execEngine.returnControlToScheduler(scheduler)) {
        std::cerr << "[FATAL ERROR [Code 1004]] Stage S7 (ExecutionEngine::returnControlToScheduler) failed.\n";
        return EXIT_FAILURE;
    }

    // Phase 8 & UI Binding (S8)
    Kravs::UserInterface ui(execEngine);
    if (!ui.renderConsole()) {
        std::cerr << "[FATAL ERROR [Code 1101]] Stage S8 (UserInterface::renderConsole) failed.\n";
        return EXIT_FAILURE;
    }
    if (!ui.logEvent("Script executed successfully without detection.")) {
        std::cerr << "[FATAL ERROR [Code 1102]] Stage S8 (UserInterface::logEvent) failed.\n";
        return EXIT_FAILURE;
    }
    if (!ui.controlExecution(true)) {
        std::cerr << "[FATAL ERROR [Code 1103]] Stage S8 (UserInterface::controlExecution) failed.\n";
        return EXIT_FAILURE;
    }
    std::string telemetryStatus;
    if (!ui.updateStatus(telemetryStatus)) {
        std::cerr << "[FATAL ERROR [Code 1104]] Stage S8 (UserInterface::updateStatus) failed.\n";
        return EXIT_FAILURE;
    }

    std::cout << "\n[+] Kravs Commit 1b pipeline execution completed successfully! S9 closing RAII cleanup initiated...\n";
    return EXIT_SUCCESS;
}
