// Copyright 2024 neov5
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstdint>
#include <atomic>
#include <string>
#include <optional>
#include <memory>
#include <array>
#include <filesystem>
#include <vector>
#include "mio.hpp"

using namespace std;

namespace usnet {
namespace pci {

struct config_header {
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t  revision_id;
    uint8_t  class_code[3];
    uint8_t  cache_line_size;
    uint8_t  lat_timer;
    uint8_t  header_type;
    uint8_t  bist;
    uint32_t bar[6];
    uint32_t cardbus_cis_pointer;
    uint16_t subsystem_vendor_id;
    uint16_t subsystem_id;
    uint32_t expansion_rom_base_addr;
    uint8_t  capabilities_pointer;
    uint8_t  reserved[7];
    uint8_t  interrupt_line;
    uint8_t  interrupt_pin;
    uint8_t  min_gnt;
    uint8_t  max_lat;
}__attribute__((packed, aligned(1)));

struct capability { 
    uint8_t cap_vndr;    /* Generic PCI field: PCI_CAP_ID_VNDR */ 
    uint8_t cap_next;    /* Generic PCI field: next ptr. */ 
    uint8_t cap_len;     /* Generic PCI field: capability length */ 
    uint8_t cfg_type;    /* Identifies the structure. */ 
    uint8_t bar;         /* Where to find it. */ 
    uint8_t id;             /* Multiple capabilities of the same type */ 
    uint8_t padding[2];  /* Pad to full dword. */ 
    uint32_t offset;     /* Offset within bar. */ 
    uint32_t length;     /* Length of the structure, in bytes. */ 
}__attribute__((packed, aligned(1)));

struct config {
    config_header header;
    std::vector<capability> capabilities;

    config(std::filesystem::path config_path);

private:
    void _parse_header(const std::vector<uint8_t>& cfg_bytes);
    void _parse_capabilities(const uint8_t cap_ptr, const std::vector<uint8_t>& cfg_bytes);
};

// note that this is a single-function device: we do not support multi-function
// devices yet.
struct device {
    // fully-qualified address: <devbus>:<bus>:<dev>.<func>
    std::string address;
    std::filesystem::path device_path;
    config cfg;
    std::array<mio::mmap_source,6> bars;

    device(std::string _address);
    void remove_driver();
    void enable_dma();
};

} // namespace pci
} // namespace usnet
