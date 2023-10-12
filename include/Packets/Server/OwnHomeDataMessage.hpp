/*
* OwnHomeDataMessage.hpp - The SolarSCore
* Copyright (C) 2023 Solar
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

#ifndef OWNHOMEDATAMESSAGE_HPP
#define OWNHOMEDATAMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"

class OwnHomeDataMessage {
public:
	OwnHomeDataMessage(int32_t sock);  /* Message init */
	static void encode();  /* Message encoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !OWNHOMEDATAMESSAGE_HPP