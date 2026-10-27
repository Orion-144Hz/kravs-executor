#ifndef INJECTOR_HPP
#define INJECTOR_HPP

#include <cstdint>
#include <string>

namespace Kravs {
class Injector {
public:
    Injector();
    ~Injector() = default;

    bool attachProcess(uint32_t processId);
    bool allocateAndWriteMemory(const void* data, size_t size, void*& allocatedAddress);
    bool mapAndExecuteModule(void* remoteAddress);

private:
    uint32_t targetProcessId_;
    void* processHandle_;
};
} // namespace Kravs

#endif // INJECTOR_HPP
