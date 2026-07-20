#pragma once

#include "Message.hpp"
#include <string>

namespace Network
{

    class Serializer
    {
    public:
        static std::string serialize(const Message &message);

        static Message deserialize(const std::string &data);
    };

}