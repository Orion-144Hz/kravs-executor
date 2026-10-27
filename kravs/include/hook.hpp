#ifndef HOOK_HPP
#define HOOK_HPP

#include <cstdint>
#include <string>

namespace Kravs {
class HookManager {
public:
    HookManager();
    ~HookManager() = default;

    bool installLuauHooks();
    bool captureThreadCalls();
    bool createTrampolines();
    bool hideMemoryModifications();
};
} // namespace Kravs

#endif // HOOK_HPP
