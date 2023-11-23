#pragma once

class IMessage
{
public:
    enum class Type : char
    {
        Undefined,
        Text,
        File
    };

#pragma pack(push, 1)

    struct Head
    {
        IMessage::Type type = Type::Undefined;
        unsigned int dataLength = {};
    };

    struct Body
    {
    };

#pragma pack(pop)

private:
};