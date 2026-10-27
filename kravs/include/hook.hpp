#ifndef HOOK_HPP
#define HOOK_HPP

#include <cstdint>
#include <string>

namespace Kravs {
class HookManager {
public:
    HookManager();
    ~HookManager();

    bool installLuauHooks();
    bool captureThreadCalls();
    bool createTrampolines();
    bool hideMemoryModifications();
    bool unhook();

    void* getTargetFunction() const;
    void* getTrampolineAddress() const;

private:
    void* targetFunctionPtr_;
    void* trampolineAddressPtr_;
    bool isInstalled_;
};
} // namespace Kravs

#endif // HOOK_HPP
