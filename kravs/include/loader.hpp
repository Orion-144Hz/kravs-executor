#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <vector>

namespace Kravs {
class Loader {
public:
    Loader();
    ~Loader() = default;

    bool verifyFile(const std::string& filepath);
    bool checkPrivileges();
    bool prepareBuffer(size_t size);
    const std::vector<uint8_t>& getBuffer() const;

private:
    std::vector<uint8_t> stagingBuffer_;
};
} // namespace Kravs

#endif // LOADER_HPP
