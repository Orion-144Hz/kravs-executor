#ifndef INJECTOR_HPP
#define INJECTOR_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace Kravs {
class Injector {
public:
    Injector();
    ~Injector();

    bool attachProcess(uint32_t processId);
    bool allocateAndWriteMemory(const uint8_t* data, size_t size, void*& allocatedAddress);
    bool mapAndExecuteModule(void* remoteAddress);
    bool cleanup();

    void* getProcessHandle() const;
    uint32_t getTargetProcessId() const;

#ifdef KRAVS_TEST_STUB
    // Test hook strictly under KRAVS_TEST_STUB
    void setSimulateWriteFailure(bool simulate);
#endif

private:
    uint32_t targetProcessId_;
    void* processHandle_;
    void* allocatedRemoteAddress_;
    size_t allocatedSize_;
    bool simulateWriteFailure_;
};
} // namespace Kravs

#endif // INJECTOR_HPP
