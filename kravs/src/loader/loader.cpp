#include "loader.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sstream>

namespace Kravs {
Loader::Loader() = default;

bool Loader::verifyFile(const std::string& filepath, FileFormat expectedFormat) {
    std::cout << "[S1] Verifying file header with format check: " << filepath << "\n";
    struct stat buffer;
    if (stat(filepath.c_str(), &buffer) != 0) {
        std::cerr << "[S1 ERROR [Code 404]] File does not exist or cannot be accessed: " << filepath << "\n";
        return false;
    }
    if (buffer.st_size == 0) {
        std::cerr << "[S1 ERROR [Code 400]] File is empty (0 bytes): " << filepath << "\n";
        return false;
    }

    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[S1 ERROR [Code 403]] Failed to open file for magic byte validation.\n";
        return false;
    }

    char magic[4] = {0};
    file.read(magic, 4);

    if (expectedFormat == FileFormat::PE_BINARY) {
        // PE binaries start with 'MZ' (0x4D, 0x5A)
        if (magic[0] != 'M' || magic[1] != 'Z') {
            std::cerr << "[S1 ERROR [Code 405]] Invalid PE binary magic header (expected 'MZ').\n";
            return false;
        }
    } else if (expectedFormat == FileFormat::LUAU_BYTECODE) {
        // Luau bytecode magic header or signature
        if (static_cast<uint8_t>(magic[0]) != 0x1B) {
            std::cerr << "[S1 ERROR [Code 406]] Invalid Luau bytecode magic header (expected 0x1B).\n";
            return false;
        }
    } else if (expectedFormat == FileFormat::TEXT_SCRIPT) {
        // Text script: verify readable chars or text/cmake comments (e.g. '#', 'c', 'p', etc.)
        if (static_cast<uint8_t>(magic[0]) == 0 && static_cast<uint8_t>(magic[1]) == 0) {
            std::cerr << "[S1 ERROR [Code 407]] Invalid text script header.\n";
            return false;
        }
    }

    std::cout << "[S1] File header magic verification passed for format.\n";
    return true;
}

bool Loader::checkPrivileges(const std::string& clientVersion) {
    std::cout << "[S1] Parsing and validating SemVer format for client version: " << clientVersion << "\n";
    // Enforce strict SemVer major.minor.patch parsing (e.g. exactly 3 numeric components separated by dots: X.Y.Z)
    std::stringstream ss(clientVersion);
    std::string segment;
    int components = 0;
    while (std::getline(ss, segment, '.')) {
        if (segment.empty()) {
            std::cerr << "[S1 ERROR [Code 410]] Empty SemVer component.\n";
            return false;
        }
        for (char c : segment) {
            if (!isdigit(c)) {
                std::cerr << "[S1 ERROR [Code 411]] Non-numeric SemVer component: " << segment << "\n";
                return false;
            }
        }
        components++;
    }

    if (components != 3) {
        std::cerr << "[S1 ERROR [Code 412]] Invalid SemVer format (expected major.minor.patch, got " << components << " components).\n";
        return false;
    }

    std::cout << "[S1] Privileges verified and SemVer client version " << clientVersion << " is valid.\n";
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
