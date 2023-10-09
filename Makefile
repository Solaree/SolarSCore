# Makefile - The SolarSCore
# Copyright (C) 2023 Solar
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

CC = g++
CCFLAGS = -I. -Wall

SRC = main.cpp
TARGET = core

DEPS = \
	Core/arc4/arc4.cpp\
	Core/Crypto.cpp\
\
	Stream/ByteStream.cpp\
\
	Packets/LogicScrollMessageFactory.cpp\
\
	Packets/Client/ClientHelloMessage.cpp\
	Packets/Client/KeepAliveMessage.cpp\
	Packets/Client/LoginMessage.cpp\
\
	Packets/Server/ServerHelloMessage.cpp\
	Packets/Server/KeepAliveOkMessage.cpp\
	Packets/Server/LoginOkMessage.cpp\
	Packets/Server/LoginFailedMessage.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^ $(CCFLAGS) $(DEPS)

clean:
	rm -f $(TARGET)