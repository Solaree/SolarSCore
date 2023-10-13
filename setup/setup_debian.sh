# setup_debian.sh - The SolarSCore
# Copyright (C) 2023 Solar
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.


#!/bin/bash

# Add i386 arch
sudo dpkg --add-architecture i386

# Update & upgrade
sudo apt update -y && sudo apt upgrade -y

# Install requirements
sudo apt install -y make build-essential g++-multilib libsodium-dev:i386

# Clear terminal session
clear

# Build binary
make