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

CC = gcc
CCFLAGS = -m32 -std=gnu17 -fPIC -I. -Wall -Wno-deprecated-declarations
CXX = g++
CXXFLAGS = -m32 -std=gnu++2b -static-libstdc++ -fPIC -I. -Wall -Wno-deprecated-declarations

LIBS = -lsodium

SRC_C = \
    Core/Crypto.c

SRC_CPP = \
    Core.cpp \
    Stream/ByteStream.cpp \
    Packets/LogicScrollMessageFactory.cpp \
    Packets/Client/ClientHelloMessage.cpp \
    Packets/Client/LoginMessage.cpp \
    Packets/Client/KeepAliveMessage.cpp \
    Packets/Server/ServerHelloMessage.cpp \
    Packets/Server/LoginOkMessage.cpp \
    Packets/Server/LoginFailedMessage.cpp \
    Packets/Server/KeepAliveOkMessage.cpp \
    Packets/Server/OwnHomeDataMessage.cpp

OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)

OUT = core

UNAME := $(shell uname)

ifeq ($(UNAME), MINGW32_NT-10.0) # For MinGW
    LIBS += -lws2_32
endif

all: $(OUT) clean_bin
$(OUT): $(OBJ_C) $(OBJ_CPP)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
clean_bin:
	rm -rf $(OBJ_C) $(OBJ_CPP)
clean:
	rm -rf $(OUT) $(OBJ_C) $(OBJ_CPP)
