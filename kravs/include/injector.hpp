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

    // Test hook for simulating write failure in negative testing
    void setSimulateWriteFailure(bool simulate);

private:
    uint32_t targetProcessId_;
    void* processHandle_;
    void* allocatedRemoteAddress_;
    size_t allocatedSize_;
    bool simulateWriteFailure_;
};
} // namespace Kravs

#endif // INJECTOR_HPP
