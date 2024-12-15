// Copyright 2024 neov5
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ioutils.hpp"
#include <bit>

namespace usnet {
namespace ioutils {

inline uint8_t read_byte(std::ifstream& in) {
    uint8_t u;
    in.read(reinterpret_cast<char*>(&u), sizeof(u));
    return u;
}

inline uint16_t read_le16(std::ifstream& in) {
    uint16_t u;
    in.read(reinterpret_cast<char*>(&u), sizeof(u));
    return to_le16(u);
}

inline uint32_t read_le32(std::ifstream& in) {
    uint32_t u;
    in.read(reinterpret_cast<char*>(&u), sizeof(u));
    return to_le32(u);
}

inline uint64_t read_le64(std::ifstream& in) {
    uint64_t u;
    in.read(reinterpret_cast<char*>(&u), sizeof(u));
    return to_le64(u);
}

inline void write_byte(std::ofstream& out, uint8_t val) {
    out.write(reinterpret_cast<char*>(&val), sizeof(val));
}
inline void write_le16(std::ofstream& out, uint16_t val) {
    uint16_t u = to_le16(val);
    out.write(reinterpret_cast<char*>(&u), sizeof(u));
}
inline void write_le32(std::ofstream& out, uint32_t val) {
    uint32_t u = to_le32(val);
    out.write(reinterpret_cast<char*>(&u), sizeof(u));
}
inline void write_le64(std::ofstream& out, uint64_t val) {
    uint64_t u = to_le64(val);
    out.write(reinterpret_cast<char*>(&u), sizeof(u));
}


constexpr uint16_t to_le16(uint16_t val) {
    if (std::endian::native == std::endian::little) return val;
    return ((val & 0xFF00) >> 8u) |
           ((val & 0x00FF) << 8u);
}

constexpr uint32_t to_le32(uint32_t val) {
    if (std::endian::native == std::endian::little) return val;
    return ((val & 0xFF000000u) >> 24u) |
           ((val & 0x00FF0000u) >>  8u) |
           ((val & 0x0000FF00u) <<  8u) |
           ((val & 0x000000FFu) << 24u);
}

constexpr uint64_t to_le64(uint64_t val) {
    if (std::endian::native == std::endian::little) return val;
    return ((val & 0xFF00000000000000u) >> 56u) |
           ((val & 0x00FF000000000000u) >> 40u) |
           ((val & 0x0000FF0000000000u) >> 24u) |
           ((val & 0x000000FF00000000u) >>  8u) |
           ((val & 0x00000000FF000000u) <<  8u) |
           ((val & 0x0000000000FF0000u) << 24u) |
           ((val & 0x000000000000FF00u) << 40u) |
           ((val & 0x00000000000000FFu) << 56u);
}

constexpr uint16_t from_le16(uint16_t val) { return to_le16(val); }
constexpr uint32_t from_le32(uint32_t val) { return to_le32(val); }
constexpr uint64_t from_le64(uint64_t val) { return to_le64(val); }

} // namespace ioutils
} // namespace usnet
