# Kravs Roblox Executor (`~/kravs`)

> **[+]Meezo Tsardom[-]**

Modular Roblox Executor implementation adhering to the 9-phase architecture pipeline (including S9 Closing Stage) and robust K-4 platform/VM dependency wiring.
*(Last updated for Commit 2 Mermaid schema synchronization)*

## Architecture & Data Flow (Mermaid Schema with 6 Mandatory Corrections)

```mermaid
graph TD
    subgraph S1 [S1: Loader & Verification]
        A1[verifyFile & checkPrivileges] -->|"doğrulama başarısız"| HATA_S1[HATA: Exit Failure]
        A1 -->|"tampon hazırla"| B1[prepareBuffer]
    end

    subgraph S2 [S2: Injection]
        B1 -->|"tampon"| C1[attachProcess & allocateAndWriteMemory]
        C1 -->|"hata/PID=0"| HATA_S2[HATA: Exit Failure]
        C1 --> map[mapAndExecuteModule]
    end

    subgraph S3 [S3: Hooking & Anti-Detection]
        map --> D1[installLuauHooks & Trampolines]
        D1 -->|"hata"| HATA_S3[HATA: Exit Failure]
    end

    subgraph S4 [S4: Environment]
        D1 --> E1[createIsolatedSandbox lua_State]
    end

    subgraph S5 [S5: API Bridge]
        E1 --> F1[wrapClientFunctions & validateArguments]
    end

    subgraph S6 [S6: Scheduler & Queue]
        F1 --> G1[ingestScript & parseBytecode]
        G1 -->|"hata"| HATA_S6[HATA: Exit Failure]
    end

    subgraph S7 [S7: Execution Engine]
        G1 -->|"bytecode"| H1[loadBytecodeToVM & createContext]
        H1 -->|"sonuç/log"| I1[Execution / Error Handling]
        I1 -->|"kontrolü geri ver"| G1
    end

    subgraph S8 [S8: UI & Output]
        I1 -->|"sonuç/log"| J1[renderConsole & Telemetry]
    end

    subgraph S9 [S9: Closing Stage]
        J1 --> K1[unhook & VirtualFreeEx & CloseHandle & Detach]
    end

    style HATA_S1 fill:#f9f,stroke:#333,stroke-width:2px
    style HATA_S2 fill:#f9f,stroke:#333,stroke-width:2px
    style HATA_S3 fill:#f9f,stroke:#333,stroke-width:2px
    style HATA_S6 fill:#f9f,stroke:#333,stroke-width:2px
```

## K-4 Platform & VM Dependencies
- **Windows API:** `OpenProcess`, `VirtualAllocEx`, `WriteProcessMemory`, `VirtualFreeEx`, `CloseHandle` (linked via CMake conditional target checks).
- **Luau VM:** Open-source Luau parser, bytecode compiler, and VM state (`lua_State*`).

## Build, Test & Run

```bash
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
./kravs_executor
```
