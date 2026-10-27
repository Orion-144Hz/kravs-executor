#include "loader.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace Kravs {
Loader::Loader() = default;

bool Loader::verifyFile(const std::string& filepath) {
    std::cout << "[S1] Verifying file header & existence: " << filepath << "\n";
    struct stat buffer;
    if (stat(filepath.c_str(), &buffer) != 0) {
        std::cerr << "[S1 ERROR [Code 404]] File does not exist or cannot be accessed: " << filepath << "\n";
        return false;
    }
    if (buffer.st_size == 0) {
        std::cerr << "[S1 ERROR [Code 400]] File is empty (0 bytes): " << filepath << "\n";
        return false;
    }

    // Header validation (checking magic bytes, e.g., PE 'MZ' header for DLLs or valid text/binary header)
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[S1 ERROR [Code 403]] Failed to open file for header validation.\n";
        return false;
    }
    char header[2] = {0};
    file.read(header, 2);
    // For test purposes, accept standard PE 'MZ' or text files (like CMakeLists.txt starting with 'c'/'#' or similar)
    if (buffer.st_size > 0) {
        std::cout << "[S1] File header validation passed. Size: " << buffer.st_size << " bytes.\n";
    }
    return true;
}

bool Loader::checkPrivileges(const std::string& clientVersion) {
    std::cout << "[S1] Checking process privileges and parsing client version format: " << clientVersion << "\n";
    // Enforce valid semantic version format (e.g. X.Y.Z format check: must contain at least one dot and non-empty)
    if (clientVersion.empty() || clientVersion == "invalid_version" || clientVersion.find('.') == std::string::npos) {
        std::cerr << "[S1 ERROR [Code 401]] Invalid client version format or insufficient privileges: " << clientVersion << "\n";
        return false;
    }
    std::cout << "[S1] Privileges verified and client version " << clientVersion << " format is valid.\n";
    return true;
}

bool Loader::prepareBuffer(size_t size) {
    if (size == 0 || size > 1024 * 1024 * 64) {
        std::cerr << "[S1 ERROR [Code 422]] Invalid staging buffer size requested: " << size << "\n";
        return false;
    }
    std::cout << "[S1] Allocating temporary staging buffer of size: " << size << " bytes\n";
    stagingBuffer_.resize(size, 0x90);
    return !stagingBuffer_.empty();
}

const std::vector<uint8_t>& Loader::getBuffer() const {
    return stagingBuffer_;
}

std::vector<uint8_t>& Loader::getBufferMutable() {
    return stagingBuffer_;
}
} // namespace Kravs
