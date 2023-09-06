#include "Stream/ByteStream.cpp"

class LoginOkMessage{
public:
	ByteStream Stream;

	void encode(int sock) {
        Stream.writeLong(0, 1); // AccountID
        Stream.writeLong(0, 1); // HomeID

        Stream.writeString("Solar"); // PassToken
        Stream.writeString(); // FacebookID
        Stream.writeString(); // GameCenterID

        Stream.writeVInt(0); // MajorVersion
        Stream.writeVInt(0); // ServerBuild
        Stream.writeVInt(0); // ContentVersion

        Stream.writeString("dev"); // ServerEnvironment

        Stream.writeVInt(0); // SessionCount
        Stream.writeVInt(0); // PlayTimeSeconds
        Stream.writeVInt(0); // DaysSinceStartedPlaying

        Stream.writeString(); // FacebookAppId
        Stream.writeString(); // ServerTime
        Stream.writeString(); // AccountCreatedDate

        Stream.writeVInt(0); // Tier

        Stream.writeString(); // GoogleServiceID

        process(sock);
    }

    void process(int sock) {
        Stream.send(20108, sock);
    }
};