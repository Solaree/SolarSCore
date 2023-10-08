CC = g++
CFLAGS = -I. -Wall

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
	$(CC) -o $@ $^ $(CFLAGS) $(DEPS)

clean:
	rm -f $(TARGET)