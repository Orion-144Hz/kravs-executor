#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>

namespace Kravs {
class Environment {
public:
    Environment();
    ~Environment() = default;

    bool createIsolatedSandbox();
    bool configureGlobalTables();
    bool restrictInternalAccess();
    bool synchronizeClientState();
};
} // namespace Kravs

#endif // ENVIRONMENT_HPP
