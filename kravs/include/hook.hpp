#ifndef HOOK_HPP
#define HOOK_HPP

#include <cstdint>
#include <string>
#include <map>

namespace Kravs {
class HookManager {
public:
    HookManager();
    ~HookManager();

    bool installLuauHooks();
    bool captureThreadCalls();
    bool createTrampolines();
    bool hideMemoryModifications();
    bool unhide();
    bool detach();
    bool unhook();

    void* getTargetFunction() const;
    void* getTrampolineAddress() const;
    bool isStealthActive() const;

private:
    std::map<void*, void*> hookTable_; // Real hook table mapping target function -> trampoline address
    bool isInstalled_;
    bool isStealthActive_;
    bool isDetached_;
};
} // namespace Kravs

#endif // HOOK_HPP
