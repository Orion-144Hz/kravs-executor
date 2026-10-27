#ifndef API_BRIDGE_HPP
#define API_BRIDGE_HPP

#include <string>
#include <vector>
#include <queue>
#include <functional>

namespace Kravs {
class ApiBridge {
public:
    ApiBridge();
    ~ApiBridge() = default;

    bool wrapClientFunctions();
    int convertTypes(const std::string& inputType, std::string& outputType);
    bool validateArguments(const std::vector<std::string>& args);
    bool queueAsyncCalls(std::function<void()> task);
    bool processQueue();

private:
    std::queue<std::function<void()>> asyncTaskQueue_;
};
} // namespace Kravs

#endif // API_BRIDGE_HPP
