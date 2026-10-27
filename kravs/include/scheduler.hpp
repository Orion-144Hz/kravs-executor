#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <string>
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
};
} // namespace Kravs

#endif // SCHEDULER_HPP
