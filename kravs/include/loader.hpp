#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <vector>

namespace Kravs {
enum class FileFormat {
    PE_BINARY,
    LUAU_BYTECODE,
    TEXT_SCRIPT
};

class Loader {
public:
    Loader();
    ~Loader() = default;

    bool verifyFile(const std::string& filepath, FileFormat expectedFormat);
    bool checkPrivileges(const std::string& clientVersion);
    bool prepareBuffer(size_t size);
    const std::vector<uint8_t>& getBuffer() const;
    std::vector<uint8_t>& getBufferMutable();

private:
    std::vector<uint8_t> stagingBuffer_;
};
} // namespace Kravs

#endif // LOADER_HPP
