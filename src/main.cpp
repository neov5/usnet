// Copyright 2024 neov5
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pci.hpp"
#include <iostream>

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage: driver <pci_id>" << std::endl;
        return 0;
    }
    std::cout << argc << " " << argv[1] << std::endl;

    usnet::pci::device dev(argv[1]);

    return 0;
}
