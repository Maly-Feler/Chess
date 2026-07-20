#pragma once

#include "Message.hpp"
#include "../game_engine/GameSnapshot.hpp"
#include "../model/Piece.hpp"
#include <string>

namespace Network
{

    class Serializer
    {
    public:
        static std::string serialize(const Message &message);
        static Message deserialize(const std::string &data);

        static std::string serializeSnapshot(const GameSnapshot &);
        static GameSnapshot deserializeSnapshot(const std::string &);
    };

}