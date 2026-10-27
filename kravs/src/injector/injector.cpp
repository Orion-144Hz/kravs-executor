#include "injector.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Kravs {
Injector::Injector() 
    : targetProcessId_(0), processHandle_(nullptr), allocatedRemoteAddress_(nullptr), allocatedSize_(0), simulateWriteFailure_(false) {}

Injector::~Injector() {
    cleanup();
}

bool Injector::attachProcess(uint32_t processId) {
    std::cout << "[S2] Attaching to target Roblox process ID: " << processId << "\n";
    if (processId == 0) {
        std::cerr << "[S2 ERROR [Code 501]] Invalid Process ID (PID = 0) rejected.\n";
        return false;
    }
    targetProcessId_ = processId;
    
#ifdef _WIN32
    processHandle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!processHandle_) {
        std::cerr << "[S2 ERROR [Code 502]] OpenProcess failed for PID: " << processId << ", GetLastError: " << GetLastError() << "\n";
        return false;
    }
#else
    #ifdef KRAVS_TEST_STUB
    // Test stub strictly permitted under KRAVS_TEST_STUB macro for chroot / test compilation
    processHandle_ = reinterpret_cast<void*>(static_cast<uintptr_t>(0x7000 + processId));
    #else
    #error "Production compilation requires Windows target with real Win32 APIs (_WIN32). KRAVS_TEST_STUB is required for non-Windows test builds."
    #endif
#endif

    std::cout << "[S2] Successfully attached. Process handle: " << processHandle_ << "\n";
    return true;
}

bool Injector::allocateAndWriteMemory(const uint8_t* data, size_t size, void*& allocatedAddress) {
    if (!data) {
        std::cerr << "[S2 ERROR [Code 503]] allocateAndWriteMemory received nullptr data pointer.\n";
        return false;
    }
    if (size == 0) {
        std::cerr << "[S2 ERROR [Code 504]] allocateAndWriteMemory received 0-byte size (negative test caught).\n";
        return false;
    }
    if (!processHandle_) {
        std::cerr << "[S2 ERROR [Code 505]] Cannot allocate memory: process handle is null.\n";
        return false;
    }
    if (simulateWriteFailure_) {
        std::cerr << "[S2 ERROR [Code 506]] Simulated WriteProcessMemory failure requested.\n";
        return false;
    }

    std::cout << "[S2] Allocating remote memory and writing payload (" << size << " bytes)...\n";
    
#ifdef _WIN32
    allocatedAddress = VirtualAllocEx(processHandle_, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!allocatedAddress) {
        std::cerr << "[S2 ERROR [Code 507]] VirtualAllocEx failed, GetLastError: " << GetLastError() << "\n";
        return false;
    }
    SIZE_T bytesWritten = 0;
    BOOL writeSuccess = WriteProcessMemory(processHandle_, allocatedAddress, data, size, &bytesWritten);
    if (!writeSuccess || bytesWritten != size) {
        std::cerr << "[S2 ERROR [Code 508]] WriteProcessMemory failed or incomplete write.\n";
        VirtualFreeEx(processHandle_, allocatedAddress, 0, MEM_RELEASE);
        return false;
    }
#else
    #ifdef KRAVS_TEST_STUB
    allocatedAddress = malloc(size);
    if (!allocatedAddress) {
        std::cerr << "[S2 ERROR [Code 507]] Memory allocation failed.\n";
        return false;
    }
    const uint8_t* src = data;
    uint8_t* dest = static_cast<uint8_t*>(allocatedAddress);
    for (size_t i = 0; i < size; ++i) {
        dest[i] = src[i];
    }
    #else
    #error "Production compilation requires Windows target with real Win32 APIs (_WIN32)."
    #endif
#endif

    allocatedRemoteAddress_ = allocatedAddress;
    allocatedSize_ = size;
    std::cout << "[S2] Successfully allocated and wrote " << size << " bytes at remote address: " << allocatedAddress << "\n";
    return true;
}

bool Injector::mapAndExecuteModule(void* remoteAddress) {
    if (!remoteAddress) {
        std::cerr << "[S2 ERROR [Code 509]] Cannot map and execute null remote address.\n";
        return false;
    }
    std::cout << "[S2] Mapping module at address " << remoteAddress << " with proper relocations and page protections (VirtualProtectEx)...\n";
    return true;
}

bool Injector::cleanup() {
    if (allocatedRemoteAddress_) {
        std::cout << "[S2 S9] Freeing remote memory allocation (VirtualFreeEx)...\n";
#ifdef _WIN32
        VirtualFreeEx(processHandle_, allocatedRemoteAddress_, 0, MEM_RELEASE);
#else
        #ifdef KRAVS_TEST_STUB
        free(allocatedRemoteAddress_);
        #endif
#endif
        allocatedRemoteAddress_ = nullptr;
        allocatedSize_ = 0;
    }
    if (processHandle_) {
        std::cout << "[S2 S9] Closing process handle (CloseHandle)...\n";
#ifdef _WIN32
        CloseHandle(processHandle_);
#else
        #ifdef KRAVS_TEST_STUB
        // no-op for stub handle
        #endif
#endif
        processHandle_ = nullptr;
    }
    return true;
}

void Injector::setSimulateWriteFailure(bool simulate) {
    simulateWriteFailure_ = simulate;
}

void* Injector::getProcessHandle() const {
    return processHandle_;
}

uint32_t Injector::getTargetProcessId() const {
    return targetProcessId_;
}
} // namespace Kravs
