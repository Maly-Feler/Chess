#pragma once

#include "Protocol.hpp"
#include <string>

namespace Network
{

    struct Message
    {
        MessageType type;
        std::string payload;
    };

}