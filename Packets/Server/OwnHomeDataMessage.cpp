/*
* LoginOkMessage.cpp - The SolarSCore
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

#include "include/Packets/Server/OwnHomeDataMessage.hpp"

string name = "Solar";
int32_t diamonds = 99999;
int32_t score = 9999;

bool isInAlliance = true;
bool isInLeague = true;
bool isInLastLeague = true;
bool nameSetByUser = false;

OwnHomeDataMessage::OwnHomeDataMessage(int32_t sock) {
	encode();
	Stream.writePacket(getMessageType(), sock);
}

void OwnHomeDataMessage::encode() {
    Stream.writeInt(0); // SecondsSinceLastSave
    Stream.writeInt(0);

    Stream.writeLong(0, 1); // ID

    Stream.writeString("{\"buildings\":[{\"data\":1000001,\"lvl\":9,\"x\":20,\"y\":20},{\"data\":1000004,\"lvl\":9,\"x\":12,\"y\":29,\"res_time\":143996},{\"data\":1000000,\"lvl\":5,\"x\":29,\"y\":14,\"units\":[],\"storage_type\":0},{\"data\":1000015,\"lvl\":0,\"x\":10,\"y\":26},{\"data\":1000014,\"lvl\":2,\"x\":28,\"y\":21},{\"data\":1000004,\"lvl\":9,\"x\":23,\"y\":32,\"res_time\":143996},{\"data\":1000002,\"lvl\":9,\"x\":17,\"y\":12,\"res_time\":143996},{\"data\":1000002,\"lvl\":9,\"x\":18,\"y\":9,\"res_time\":143996},{\"data\":1000015,\"lvl\":0,\"x\":31,\"y\":25},{\"data\":1000003,\"lvl\":9,\"x\":12,\"y\":26},{\"data\":1000005,\"lvl\":9,\"x\":16,\"y\":28},{\"data\":1000006,\"lvl\":7,\"x\":9,\"y\":30,\"unit_prod\":{\"unit_type\":0}},{\"data\":1000008,\"lvl\":10,\"x\":24,\"y\":25},{\"data\":1000008,\"lvl\":10,\"x\":13,\"y\":20},{\"data\":1000002,\"lvl\":9,\"x\":25,\"y\":10,\"res_time\":143996},{\"data\":1000004,\"lvl\":9,\"x\":11,\"y\":13,\"res_time\":143996},{\"data\":1000006,\"lvl\":7,\"x\":14,\"y\":12,\"unit_prod\":{\"unit_type\":0}},{\"data\":1000009,\"lvl\":10,\"x\":17,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":13,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":12,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":22},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":21},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":15},{\"data\":1000010,\"lvl\":5,\"x\":22,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":21,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":21,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":12,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":26,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":22,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":17},{\"data\":1000010,\"lvl\":5,\"x\":25,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":26,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":25},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":17},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":18},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":12,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":26,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":25,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":25,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":29,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":18},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":18},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":31,\"y\":21},{\"data\":1000010,\"lvl\":5,\"x\":30,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":17},{\"data\":1000010,\"lvl\":5,\"x\":31,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":26},{\"data\":1000002,\"lvl\":9,\"x\":10,\"y\":16,\"res_time\":143996},{\"data\":1000004,\"lvl\":9,\"x\":9,\"y\":19,\"res_time\":143996},{\"data\":1000005,\"lvl\":9,\"x\":13,\"y\":16},{\"data\":1000003,\"lvl\":9,\"x\":25,\"y\":13},{\"data\":1000000,\"lvl\":5,\"x\":18,\"y\":32,\"units\":[],\"storage_type\":0},{\"data\":1000013,\"lvl\":3,\"x\":24,\"y\":21},{\"data\":1000007,\"lvl\":3,\"x\":21,\"y\":8},{\"data\":1000002,\"lvl\":9,\"x\":9,\"y\":22,\"res_time\":143996},{\"data\":1000004,\"lvl\":9,\"x\":28,\"y\":11,\"res_time\":143996},{\"data\":1000009,\"lvl\":10,\"x\":25,\"y\":17},{\"data\":1000012,\"lvl\":3,\"x\":21,\"y\":17},{\"data\":1000006,\"lvl\":7,\"x\":24,\"y\":29,\"unit_prod\":{\"unit_type\":0}},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":12,\"y\":21},{\"data\":1000010,\"lvl\":5,\"x\":13,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":14,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":25},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":26},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":18,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":17,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":22},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":21},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":20},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":17,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":18,\"y\":19},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":25,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":26,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":25},{\"data\":1000010,\"lvl\":5,\"x\":29,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":30,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":15},{\"data\":1000010,\"lvl\":5,\"x\":18,\"y\":15},{\"data\":1000010,\"lvl\":5,\"x\":31,\"y\":22},{\"data\":1000010,\"lvl\":5,\"x\":31,\"y\":23},{\"data\":1000010,\"lvl\":5,\"x\":31,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":27,\"y\":26},{\"data\":1000010,\"lvl\":5,\"x\":18,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":17,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":27},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":26},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":25},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":18},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":17},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":16},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":15},{\"data\":1000010,\"lvl\":5,\"x\":17,\"y\":15},{\"data\":1000010,\"lvl\":5,\"x\":12,\"y\":22},{\"data\":1000010,\"lvl\":5,\"x\":14,\"y\":23},{\"data\":1000002,\"lvl\":9,\"x\":15,\"y\":32,\"res_time\":143996},{\"data\":1000004,\"lvl\":9,\"x\":28,\"y\":29,\"res_time\":143996},{\"data\":1000008,\"lvl\":10,\"x\":16,\"y\":24},{\"data\":1000013,\"lvl\":3,\"x\":17,\"y\":20},{\"data\":1000000,\"lvl\":5,\"x\":32,\"y\":19,\"units\":[],\"storage_type\":0},{\"data\":1000009,\"lvl\":10,\"x\":20,\"y\":28},{\"data\":1000011,\"lvl\":2,\"x\":20,\"y\":24},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":29},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":30},{\"data\":1000010,\"lvl\":5,\"x\":19,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":21,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":22,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":30},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":29},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":14},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":13},{\"data\":1000010,\"lvl\":5,\"x\":20,\"y\":12},{\"data\":1000010,\"lvl\":5,\"x\":21,\"y\":12},{\"data\":1000010,\"lvl\":5,\"x\":22,\"y\":12},{\"data\":1000010,\"lvl\":5,\"x\":23,\"y\":12},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":12},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":13},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":14},{\"data\":1000010,\"lvl\":5,\"x\":24,\"y\":15},{\"data\":1000010,\"lvl\":5,\"x\":18,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":17,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":16,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":31},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":30},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":29},{\"data\":1000010,\"lvl\":5,\"x\":15,\"y\":28},{\"data\":1000011,\"lvl\":2,\"x\":21,\"y\":13},{\"data\":1000020,\"lvl\":1,\"x\":28,\"y\":25,\"units\":[],\"storage_type\":1,\"unit_prod\":{\"unit_type\":1}},{\"data\":1000010,\"lvl\":5,\"x\":29,\"y\":28},{\"data\":1000010,\"lvl\":5,\"x\":28,\"y\":28}],\"obstacles\":[{\"data\":8000008,\"x\":6,\"y\":6,\"loot_multiply_ver\":1},{\"data\":8000005,\"x\":37,\"y\":5,\"loot_multiply_ver\":1},{\"data\":8000007,\"x\":6,\"y\":4,\"loot_multiply_ver\":1},{\"data\":8000008,\"x\":35,\"y\":7,\"loot_multiply_ver\":1},{\"data\":8000005,\"x\":5,\"y\":29,\"loot_multiply_ver\":1},{\"data\":8000002,\"x\":4,\"y\":38,\"loot_multiply_ver\":1},{\"data\":8000008,\"x\":5,\"y\":36,\"loot_multiply_ver\":1},{\"data\":8000001,\"x\":7,\"y\":35,\"loot_multiply_ver\":1},{\"data\":8000007,\"x\":4,\"y\":9,\"loot_multiply_ver\":1},{\"data\":8000003,\"x\":29,\"y\":37,\"loot_multiply_ver\":1},{\"data\":8000001,\"x\":33,\"y\":4,\"loot_multiply_ver\":1},{\"data\":8000010,\"x\":26,\"y\":38,\"loot_multiply_ver\":1},{\"data\":8000013,\"x\":34,\"y\":33,\"loot_multiply_ver\":1},{\"data\":8000007,\"x\":32,\"y\":38,\"loot_multiply_ver\":1},{\"data\":8000000,\"x\":12,\"y\":8,\"loot_multiply_ver\":1},{\"data\":8000005,\"x\":4,\"y\":20,\"loot_multiply_ver\":1},{\"data\":8000005,\"x\":32,\"y\":10,\"loot_multiply_ver\":1},{\"data\":8000000,\"x\":38,\"y\":13,\"loot_multiply_ver\":1},{\"data\":8000013,\"x\":1,\"y\":34,\"loot_multiply_ver\":1},{\"data\":8000006,\"x\":1,\"y\":19,\"loot_multiply_ver\":1},{\"data\":8000000,\"x\":40,\"y\":29,\"loot_multiply_ver\":1}],\"traps\":[{\"data\":12000000,\"lvl\":2,\"x\":14,\"y\":15},{\"data\":12000000,\"lvl\":2,\"x\":27,\"y\":29},{\"data\":12000001,\"lvl\":0,\"x\":32,\"y\":24},{\"data\":12000001,\"lvl\":0,\"x\":28,\"y\":15},{\"data\":12000000,\"lvl\":2,\"x\":27,\"y\":30},{\"data\":12000000,\"lvl\":2,\"x\":29,\"y\":19},{\"data\":12000001,\"lvl\":0,\"x\":15,\"y\":15},{\"data\":12000001,\"lvl\":0,\"x\":14,\"y\":32},{\"data\":12000005,\"lvl\":1,\"x\":11,\"y\":29},{\"data\":12000005,\"lvl\":1,\"x\":30,\"y\":28},{\"data\":12000002,\"lvl\":1,\"x\":13,\"y\":24}],\"decos\":[],\"respawnVars\":{\"secondsFromLastRespawn\":7200,\"respawnSeed\":561881117,\"obstacleClearCounter\":16,\"time_to_gembox_drop\":5,\"time_in_gembox_period\":1},\"cooldowns\":[],\"newShopBuildings\":[3,0,6,2,6,2,3,1,3,3,125,2,1,2,1,5,0,0,0,0,1,0,0,0,0,0,0,0],\"newShopTraps\":[4,4,1,0,0,2,0,0],\"newShopDecos\":[1,4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],\"last_league_rank\":0,\"last_league_shuffle\":0,\"last_news_seen\":58,\"edit_mode_shown\":false,\"war_tutorials_seen\":0,\"war_base\":false}"); // HomeJSON

    Stream.writeInt(0); // ShieldDurationSeconds
    Stream.writeInt(0); // DefenseRaiting
    Stream.writeInt(0); // DefenseKFactor

    Stream.writeInt(0);

    Stream.writeLong(0, 1); // DefaultID
    Stream.writeLong(0, 1); // CurrentHomeID

    Stream.writeBool(isInAlliance); // IsInAlliance

    if (isInAlliance) {
        Stream.writeLong(0, 1); // AllianceID
        Stream.writeString("SolarLand"); // AllianceName
        Stream.writeLong(13, 0); // AllianceBadge
        Stream.writeInt(0); // AllianceRole
    }

    Stream.writeBool(isInLeague); // IsInLeague

    if (isInLeague)
        Stream.writeLong(0, 1); // LeagueID

    Stream.writeBool(isInLastLeague); // IsInLastLeague

    if (isInLastLeague) {
        Stream.writeLong(0, 1); // LastLeagueID
        Stream.writeInt(11); // LeagueType
    }

    Stream.writeInt(0);
    Stream.writeInt(10);
    Stream.writeInt(0);
    Stream.writeInt(0);

    if (!nameSetByUser)
        Stream.writeString(name); // Name
    else
        Stream.writeString(); // Name

    Stream.writeString(); // FacebookID

    Stream.writeInt(99); // ExpLevel
    Stream.writeInt(999); // ExpPoints
    Stream.writeInt(diamonds); // Diamonds
    Stream.writeInt(0); // FreeDiamonds
    Stream.writeInt(0); // AttackRaiting
    Stream.writeInt(0); // AttackKFactor
    Stream.writeInt(score); // Score
    Stream.writeInt(0); // AttackWinCount
    Stream.writeInt(0); // AttackLoseCount
    Stream.writeInt(0); // DefenseWinCount
    Stream.writeInt(0); // DefenseLoseCount
    Stream.writeInt(0);
    Stream.writeInt(0);
    Stream.writeInt(0);

    Stream.writeBool(nameSetByUser); // NameSetByUser
    Stream.writeBool(false);

    Stream.writeInt(0); // CumulativePurchasedDiamonds

    for (int32_t i = 0; i < 16; i++) // Arrays
        Stream.writeInt(0);
}

const uint16_t OwnHomeDataMessage::getMessageType() {
	return 24101;
}