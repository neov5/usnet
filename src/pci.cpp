// Copyright 2024 neov5
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pci.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <bit>
#include "mio.hpp"
#include <cassert>

#include <cstdio>
#include <sys/stat.h>

namespace usnet {
namespace pci {

config::config(std::filesystem::path config_path): capabilities{} {

    std::cout << config_path << std::endl;

    std::ifstream in(config_path, std::ios::binary);
    if (in.fail()) {
        throw runtime_error("Could not open config");
    }
    in.seekg(0, std::ios::end);
    auto len = in.tellg();
    in.seekg(0, std::ios::beg);
    std::vector<uint8_t> cfg_bytes(len);
    in.read(reinterpret_cast<char*>(cfg_bytes.data()), len);

    uint8_t* cfg_byte_ptr = cfg_bytes.data();
    size_t cfg_n_bytes = cfg_bytes.size();

    std::cout << "Read bytes from config" << std::endl;

    config::_parse_header(cfg_bytes);
    config::_parse_capabilities(header.capabilities_pointer, cfg_bytes);
}

void config::_parse_header(const std::vector<uint8_t>& cfg_bytes) {

    header = *reinterpret_cast<const config_header*>(cfg_bytes.data());

    if constexpr (std::endian::native == std::endian::big) {
        throw runtime_error("Parsing header not implemented for big endian systems");
    }
    std::cout << "Read header" << std::endl;
}

void config::_parse_capabilities(uint8_t cap_offset, const std::vector<uint8_t>& cfg_bytes) {
    while (cap_offset != 0) {
        capability cap = *reinterpret_cast<const capability*>(cfg_bytes.data()+cap_offset);
        if constexpr (std::endian::native == std::endian::big) {
            throw runtime_error("Parsing header not implemented for big endian systems");
        }
        capabilities.push_back(cap);
        cap_offset = cap.cap_next;
    }
    std::cout << "Read capabilities" << std::endl;
}

device::device(std::string addr): 
    address{addr}, 
    device_path(std::filesystem::path("/sys/bus/pci/devices") / addr), 
    cfg{device_path / "config"} {

    remove_driver();

    for (int i=0; i<6; i++) {
        auto resource_path = device_path / std::format("resource{}", i);
        if (std::filesystem::exists(resource_path) and ((cfg.header.bar[i] & 0x1) == 0)) {
            bars[i] = mio::mmap_source(resource_path.string()); 
        }
    }
}

void device::remove_driver() {
    ofstream out(device_path / "driver/unbind");
    out << address;
}

} // namespace pci
} // namespace usnet
