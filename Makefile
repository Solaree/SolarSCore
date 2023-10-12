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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

CXX = g++
CXXFLAGS = -m32 -std=gnu++2a -static-libstdc++ -fPIC -I. -Wall -Wno-deprecated-declarations

SRC = core.cpp
OUT = core

DEPS = \
	Core/Crypto.c\
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
	Packets/Server/LoginFailedMessage.cpp\
	Packets/Server/OwnHomeDataMessage.cpp

LIBS = -lcrypto

UNAME := $(shell uname)

ifeq ($(UNAME), MINGW32_NT-10.0) # For Windows using MinGW
    LIBS += -lws2_32
endif

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(DEPS) $(LIBS)

clean:
	rm -rf $(OUT)
