#pragma once

#include <unordered_map>
#include <functional>

#include "../../shared/base/LogicMessageFactory.h"

#include "../../protocol/message/Messages.h"

#define add_message(type, name) allMessages.emplace(type, []() {return new name();});

class LogicSlashMessageFactory : public LogicMessageFactory {
private:
    std::unordered_map<int, std::function<PiranhaMessage*()>> allMessages;
public:
    LogicSlashMessageFactory() {
        add_message(10100, ClientHelloMessage);
        add_message(10101, LoginMessage);
        add_message(17141, AvatarNameCheckRequestMessage);
        add_message(13925, QuestGetDataReqMessage);
        add_message(14731, DSClusterReqMessage);
        add_message(10108, KeepAliveMessage);
        add_message(16666, AgeGateReqMessage);
        add_message(11500, HomeServerSettingReqMessage);
        add_message(15998, BattleStateCheckReqMessage);
        add_message(18867, HomePlayerDataReqMessage);
        add_message(16845, HomeReadGenericStorageReqMessage);
        add_message(14123, LeaderboardGetCurrentRankReqMessage);
        add_message(12727, VoiceChatVerifyAgeResultReqMessage);
        add_message(15332, LeaderboardInfoReqMessage);
        add_message(18666, SeasonShopFullInfoReqMessage);
        add_message(19228, MatchMakeStartReqMessage);
        add_message(10099, ClientCryptoErrorMessage);
    }

    PiranhaMessage* CreateMessageByType(int messageType) override {
        auto it = allMessages.find(messageType);

        if (it == allMessages.end()) return nullptr;

        return it->second();
    }
};