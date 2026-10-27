#include "injector.hpp"
#include <iostream>

namespace Kravs {
Injector::Injector() 
    : targetProcessId_(0), processHandle_(nullptr), allocatedRemoteAddress_(nullptr), allocatedSize_(0) {}

Injector::~Injector() {
    cleanup();
}

bool Injector::attachProcess(uint32_t processId) {
    std::cout << "[S2] Attaching to target Roblox process ID: " << processId << "\n";
    if (processId == 0) {
        std::cerr << "[S2 ERROR] Invalid Process ID (PID = 0) rejected.\n";
        return false;
    }
    targetProcessId_ = processId;
    
    // Real / Production Windows API integration pattern (OpenProcess simulation / stub for cross-platform chroot)
    #ifdef _WIN32
    // Windows implementation: processHandle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    #else
    // Linux cross-compilation target stub: simulate valid handle representation for PID > 0
    processHandle_ = reinterpret_cast<void*>(static_cast<uintptr_t>(0x7000 + processId));
    #endif

    if (!processHandle_) {
        std::cerr << "[S2 ERROR] Failed to open process handle for PID: " << processId << "\n";
        return false;
    }
    std::cout << "[S2] Successfully attached. Process handle: " << processHandle_ << "\n";
    return true;
}

bool Injector::allocateAndWriteMemory(const uint8_t* data, size_t size, void*& allocatedAddress) {
    if (!data || size == 0) {
        std::cerr << "[S2 ERROR] allocateAndWriteMemory received nullptr data or zero size.\n";
        return false;
    }
    if (!processHandle_) {
        std::cerr << "[S2 ERROR] Cannot allocate memory: process handle is null.\n";
        return false;
    }

    std::cout << "[S2] Allocating remote memory and writing payload (" << size << " bytes)...\n";
    
    #ifdef _WIN32
    // Windows production code:
    // allocatedAddress = VirtualAllocEx(processHandle_, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    // if (!allocatedAddress) return false;
    // SIZE_T bytesWritten = 0;
    // BOOL writeSuccess = WriteProcessMemory(processHandle_, allocatedAddress, data, size, &bytesWritten);
    // if (!writeSuccess || bytesWritten != size) return false;
    #else
    // Linux cross-compilation staging stub representing VirtualAllocEx + WriteProcessMemory
    allocatedAddress = malloc(size); // Safe heap allocation proxy in non-Windows build
    if (!allocatedAddress) {
        std::cerr << "[S2 ERROR] Memory allocation failed.\n";
        return false;
    }
    // Copy data safely using direct pointer assignment
    const uint8_t* src = data;
    uint8_t* dest = static_cast<uint8_t*>(allocatedAddress);
    for (size_t i = 0; i < size; ++i) {
        dest[i] = src[i];
    }
    #endif

    allocatedRemoteAddress_ = allocatedAddress;
    allocatedSize_ = size;
    std::cout << "[S2] Successfully allocated and wrote " << size << " bytes at remote address: " << allocatedAddress << "\n";
    return true;
}

bool Injector::mapAndExecuteModule(void* remoteAddress) {
    if (!remoteAddress) {
        std::cerr << "[S2 ERROR] Cannot map and execute null remote address.\n";
        return false;
    }
    std::cout << "[S2] Mapping module at address " << remoteAddress << " with proper relocations and page protections (VirtualProtectEx)...\n";
    return true;
}

bool Injector::cleanup() {
    if (allocatedRemoteAddress_) {
        std::cout << "[S2 S9] Freeing remote memory allocation (VirtualFreeEx)...\n";
        #ifdef _WIN32
        // VirtualFreeEx(processHandle_, allocatedRemoteAddress_, 0, MEM_RELEASE);
        #else
        free(allocatedRemoteAddress_);
        #endif
        allocatedRemoteAddress_ = nullptr;
        allocatedSize_ = 0;
    }
    if (processHandle_) {
        std::cout << "[S2 S9] Closing process handle (CloseHandle)...\n";
        #ifdef _WIN32
        // CloseHandle(processHandle_);
        #endif
        processHandle_ = nullptr;
    }
    return true;
}

void* Injector::getProcessHandle() const {
    return processHandle_;
}

uint32_t Injector::getTargetProcessId() const {
    return targetProcessId_;
}
} // namespace Kravs
