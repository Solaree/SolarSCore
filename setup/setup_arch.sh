# setup_arch.sh - The SolarSCore
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

# Enable multilib repository
sudo sed -i "/\[multilib\]/,/Include/"'s/^#//' /etc/pacman.conf

# Update & upgrade
sudo pacman -Syu --noconfirm

# Install requirements for multilib
sudo pacman -S --noconfirm --needed base-devel multilib-devel lib32-libsodium

# Clear terminal session
clear

# Build binary
make