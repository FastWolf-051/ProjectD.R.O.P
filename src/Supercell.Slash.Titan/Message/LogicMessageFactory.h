#pragma once

class PiranhaMessage;

class LogicMessageFactory {
public:
    LogicMessageFactory() {}

    virtual PiranhaMessage* CreateMessageByType(int messageType) = 0;

    virtual ~LogicMessageFactory() {}
};