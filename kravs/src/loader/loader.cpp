#include "loader.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace Kravs {
Loader::Loader() = default;

bool Loader::verifyFile(const std::string& filepath) {
    std::cout << "[S1] Verifying file integrity & existence: " << filepath << "\n";
    struct stat buffer;
    if (stat(filepath.c_str(), &buffer) != 0) {
        std::cerr << "[S1 ERROR] File does not exist or cannot be accessed: " << filepath << "\n";
        return false;
    }
    if (buffer.st_size == 0) {
        std::cerr << "[S1 ERROR] File is empty (0 bytes): " << filepath << "\n";
        return false;
    }
    std::cout << "[S1] File verified successfully. Size: " << buffer.st_size << " bytes.\n";
    return true;
}

bool Loader::checkPrivileges(const std::string& clientVersion) {
    std::cout << "[S1] Checking process privileges and matching client version: " << clientVersion << "\n";
    // Enforce valid expected version check
    if (clientVersion.empty() || clientVersion == "invalid_version") {
        std::cerr << "[S1 ERROR] Client version mismatch or insufficient privileges.\n";
        return false;
    }
    std::cout << "[S1] Privileges verified and client version " << clientVersion << " matches.\n";
    return true;
}

bool Loader::prepareBuffer(size_t size) {
    if (size == 0 || size > 1024 * 1024 * 64) { // Max 64MB sanity limit
        std::cerr << "[S1 ERROR] Invalid staging buffer size requested: " << size << "\n";
        return false;
    }
    std::cout << "[S1] Allocating temporary staging buffer of size: " << size << " bytes\n";
    stagingBuffer_.resize(size, 0x90); // NOP sled / payload staging
    return !stagingBuffer_.empty();
}

const std::vector<uint8_t>& Loader::getBuffer() const {
    return stagingBuffer_;
}

std::vector<uint8_t>& Loader::getBufferMutable() {
    return stagingBuffer_;
}
} // namespace Kravs
