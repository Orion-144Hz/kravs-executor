#ifndef API_BRIDGE_HPP
#define API_BRIDGE_HPP

#include <string>
#include <vector>

namespace Kravs {
class ApiBridge {
public:
    ApiBridge();
    ~ApiBridge() = default;

    bool wrapClientFunctions();
    bool convertTypes();
    bool validateArguments();
    bool queueAsyncCalls();
};
} // namespace Kravs

#endif // API_BRIDGE_HPP
