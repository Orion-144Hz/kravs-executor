#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>

namespace Kravs {
class Environment {
public:
    Environment();
    ~Environment();

    bool createIsolatedSandbox();
    bool configureGlobalTables();
    bool restrictInternalAccess();
    bool synchronizeClientState();
    bool destroyState();

    void* getLuauState() const;

private:
    void* luauState_; // Represents Luau lua_State* instance
    bool isSandboxActive_;
};
} // namespace Kravs

#endif // ENVIRONMENT_HPP
