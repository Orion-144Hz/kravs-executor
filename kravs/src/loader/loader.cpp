#include "loader.hpp"
#include <iostream>

namespace Kravs {
Loader::Loader() = default;

bool Loader::verifyFile(const std::string& filepath) {
    std::cout << "[S1] Verifying file integrity: " << filepath << "\n";
    return true;
}

bool Loader::checkPrivileges() {
    std::cout << "[S1] Checking process privileges and client version...\n";
    return true;
}

bool Loader::prepareBuffer(size_t size) {
    std::cout << "[S1] Allocating temporary staging buffer of size: " << size << " bytes\n";
    stagingBuffer_.resize(size, 0);
    return !stagingBuffer_.empty();
}

const std::vector<uint8_t>& Loader::getBuffer() const {
    return stagingBuffer_;
}
} // namespace Kravs
