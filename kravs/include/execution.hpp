#ifndef EXECUTION_HPP
#define EXECUTION_HPP

#include <string>
#include <vector>

namespace Kravs {
class Environment;
class Scheduler;

class ExecutionEngine {
public:
    ExecutionEngine();
    ~ExecutionEngine() = default;

    bool loadBytecodeToVM(const std::vector<uint8_t>& bytecode, Environment& env);
    bool createContext();
    bool handleErrors();
    bool returnControlToScheduler(Scheduler& scheduler);

    bool isExecuted() const;

private:
    bool isExecuted_;
    size_t loadedBytecodeSize_;
};
} // namespace Kravs

#endif // EXECUTION_HPP
