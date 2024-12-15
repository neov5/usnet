// Copyright 2024 neov5
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <fstream>
#include <cinttypes>

namespace usnet {
namespace ioutils {

inline uint8_t  read_byte(std::ifstream& in);
inline uint16_t read_le16(std::ifstream& in);
inline uint32_t read_le32(std::ifstream& in);
inline uint64_t read_le64(std::ifstream& in);

template<size_t num>
inline std::array<uint8_t, num> read_bytearr(std::ifstream& in);
template<size_t num>
inline std::array<uint16_t, num> read_le16arr(std::ifstream& in);
template<size_t num>
inline std::array<uint32_t, num> read_le32arr(std::ifstream& in);
template<size_t num>
inline std::array<uint64_t, num> read_le64arr(std::ifstream& in);

inline void write_byte(std::ofstream& out, uint8_t  value);
inline void write_le16(std::ofstream& out, uint16_t value);
inline void write_le32(std::ofstream& out, uint32_t value);
inline void write_le64(std::ofstream& out, uint64_t value);

constexpr uint16_t to_le16(uint16_t value);
constexpr uint32_t to_le32(uint32_t value);
constexpr uint64_t to_le64(uint64_t value);

constexpr uint16_t from_le16(uint16_t value);
constexpr uint32_t from_le32(uint32_t value);
constexpr uint64_t from_le64(uint64_t value);


} // namespace ioutils
} // namespace usnet
