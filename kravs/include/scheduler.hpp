#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <string>
#include <vector>
#include <queue>

namespace Kravs {
class Scheduler {
public:
    Scheduler();
    ~Scheduler() = default;

    bool ingestScript(const std::string& script);
    bool parseBytecode();
    bool enqueueTask(const std::string& taskName);
    bool managePriorities();
    bool cancelTask(const std::string& taskName);
    bool rerunTask(const std::string& taskName);

    const std::vector<uint8_t>& getCompiledBytecode() const;
    const std::string& getCurrentScript() const;

private:
    std::string currentScript_;
    std::vector<uint8_t> compiledBytecode_;
    std::queue<std::string> taskQueue_;
    bool isCancelled_;
};
} // namespace Kravs

#endif // SCHEDULER_HPP
