#include <iostream>
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

    Kravs::Loader loader;
    loader.verifyFile("roblox_client_core.dll");
    loader.checkPrivileges();
    loader.prepareBuffer(4096);

    Kravs::Injector injector;
    injector.attachProcess(1337);
    void* addr = nullptr;
    injector.allocateAndWriteMemory(loader.getBuffer().data(), loader.getBuffer().size(), addr);
    injector.mapAndExecuteModule(addr);

    Kravs::HookManager hookMgr;
    hookMgr.installLuauHooks();
    hookMgr.captureThreadCalls();
    hookMgr.createTrampolines();
    hookMgr.hideMemoryModifications();

    Kravs::Environment env;
    env.createIsolatedSandbox();
    env.configureGlobalTables();
    env.restrictInternalAccess();
    env.synchronizeClientState();

    Kravs::ApiBridge bridge;
    bridge.wrapClientFunctions();
    bridge.convertTypes();
    bridge.validateArguments();
    bridge.queueAsyncCalls();

    Kravs::Scheduler scheduler;
    scheduler.ingestScript("print('Kravs Executor loaded successfully!')");
    scheduler.parseBytecode();
    scheduler.enqueueTask("MainExecutionTask");
    scheduler.managePriorities();

    Kravs::ExecutionEngine execEngine;
    execEngine.loadBytecodeToVM("compiled_luau_bytecode_chunk");
    execEngine.createContext();
    execEngine.handleErrors();
    execEngine.returnControlToScheduler();

    Kravs::UserInterface ui;
    ui.renderConsole();
    ui.logEvent("Script executed successfully without detection.");
    ui.controlExecution(true);
    ui.updateStatus();

    std::cout << "\n[+] Kravs pipeline execution completed successfully!\n";
    return 0;
}
