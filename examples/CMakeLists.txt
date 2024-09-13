# SPDX-License-Identifier: BSD-3-Clause
# 
# Copyright (c) 2024 Simone Palacino <simo.palacino@gmail.com>
# All rights reserved.
# 
# Redistribution and use in source or binary forms are permitted provided that
# the following conditions are met: (1) source code retains the copyright notice
# and disclaimer, (2) binary forms reproduce the copyright notice and disclaimer,
# (3) neither the name of Trm nor its contributors may be used to
# endorse or promote derived products without permission.
# 
# For the full license text, see the LICENSE file.
# 

# Get all example source files
file(GLOB EXAMPLE_SOURCES *.cpp)

include_directories("../include/")

# Add an executable for each example
foreach(EXAMPLE_FILE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
endforeach()
