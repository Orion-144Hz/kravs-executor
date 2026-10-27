#ifndef EXECUTION_HPP
#define EXECUTION_HPP

#include <string>

namespace Kravs {
class ExecutionEngine {
public:
    ExecutionEngine();
    ~ExecutionEngine() = default;

    bool loadBytecodeToVM(const std::string& bytecode);
    bool createContext();
    bool handleErrors();
    bool returnControlToScheduler();
};
} // namespace Kravs

#endif // EXECUTION_HPP
