#pragma once

#include "../../logic/Message/Messages.h"

#include "../Networking/Connection/ClientConnection.h"

#include "../../titan/Debug/Debugger.h"
#include "../../titan/Message/PiranhaMessage.h"
#include "../../logic/Utils/PassToken.h"

#define cast_class(message, type) static_cast<type*>(message)

class MessageManager {
private:
    ClientConnection* _connection;

    int _lastReceivedMessageIndex;
public:
    MessageManager(ClientConnection* connection) {
        _connection = connection;

        _lastReceivedMessageIndex = 0;
    }

    void ReceiveMessage(PiranhaMessage* message) {
        if (message == nullptr) return;

        _lastReceivedMessageIndex = message->GetMessageIndex();
        
        switch (message->GetMessageType()) {
            // On(cast_class(message, ));
            case 10100:
                OnClientHelloMessage(cast_class(message, ClientHelloMessage));
                break;
            case 10101:
                OnLoginMessage(cast_class(message, LoginMessage));
                break;
            case 17141:
                OnAvatarNameCheckRequestMessage(cast_class(message, AvatarNameCheckRequestMessage));
                break;
            case 13925:
                OnQuestGetDataReqMessage(cast_class(message, QuestGetDataReqMessage));
                break;
            case 14731:
                OnDSClusterReqMessage(cast_class(message, DSClusterReqMessage));
                break;
            case 10108:
                OnKeepAliveMessage(cast_class(message, KeepAliveMessage));
                break;
            case 16666:
                OnAgeGateReqMessage(cast_class(message, AgeGateReqMessage));
                break;
            case 11500:
                OnHomeServerSettingReqMessage(cast_class(message, HomeServerSettingReqMessage));
                break;
            case 15998:
                OnBattleStateCheckReqMessage(cast_class(message, BattleStateCheckReqMessage));
                break;
            case 18867:
                OnHomePlayerDataReqMessage(cast_class(message, HomePlayerDataReqMessage));
                break;
            case 16845:
                OnHomeReadGenericStorageReqMessage(cast_class(message, HomeReadGenericStorageReqMessage));
                break;
            case 14123:
                OnLeaderboardGetCurrentRankReqMessage(cast_class(message, LeaderboardGetCurrentRankReqMessage));
                break;
            case 12727:
                OnVoiceChatVerifyAgeResultReqMessage(cast_class(message, VoiceChatVerifyAgeResultReqMessage));
                break;
            case 19228:
                OnMatchMakeStartReqMessage(cast_class(message, MatchMakeStartReqMessage));
                break;
            case 15332:
                OnLeaderboardInfoReqMessage(cast_class(message, LeaderboardInfoReqMessage));
                break;
            case 18666:
                OnSeasonShopFullInfoReqMessage(cast_class(message, SeasonShopFullInfoReqMessage));
                break;
            case 10099:
                OnClientCryptoErrorMessage(cast_class(message, ClientCryptoErrorMessage));
                break;
        }
    }

    int GetLastReceivedMessageIndex() {
        return _lastReceivedMessageIndex;
    }
    
private:
    void OnClientHelloMessage(ClientHelloMessage* message) {
        Debugger::Print("[ClientHelloMessage]: nope");

        _connection->SendMessage(new ServerHelloMessage());
    }

    void OnLoginMessage(LoginMessage* message) {
        Debugger::Print("[LoginMessage]: accountId: %s, clientVersion: %s, passToken: %s, device: %s",
            message->GetAccountId().ToString(), message->GetClientVersion().c_str(),
            message->GetPassToken().c_str(), message->GetDeviceInfo().c_str()
        );

        LoginOkMessage* loginOk = new LoginOkMessage();
        loginOk->SetAvatarId(LogicLong(0, 13));
        loginOk->SetAccountId(LogicLong(0, 54));
        loginOk->SetPassToken(PassToken::Generate());
        loginOk->SetServerVersion(0, 3, 296710);
        loginOk->SetServerEnvironment("beta");
        loginOk->SetServerTime("1787153808616");
        loginOk->SetAccountCreatedDate("2026-08-19T15:36:49Z");
        loginOk->SetLoginCountry("DE");

        _connection->SendMessage(loginOk);
    }

    void OnAvatarNameCheckRequestMessage(AvatarNameCheckRequestMessage* message) {
        Debugger::Print("[AvatarNameCheckRequestMessage]: avatarName: %s", message->GetAvatarName().c_str());

        _connection->SendMessage(new AvatarNameCheckResponseMessage());
    }

    void OnQuestGetDataReqMessage(QuestGetDataReqMessage* message) {
        Debugger::Print("[QuestGetDataReqMessage]: nope");

        _connection->SendMessage(new QuestGetDataRspMessage());
    }

    void OnDSClusterReqMessage(DSClusterReqMessage* message) {
        Debugger::Print("[DSClusterReqMessage]: nope");

        _connection->SendMessage(new DSClusterRspMessage());
    }

    void OnKeepAliveMessage(KeepAliveMessage* message) {
        Debugger::Print("[KeepAliveMessage]: nope");

        _connection->SendMessage(new KeepAliveServerMessage());
    }

    void OnAgeGateReqMessage(AgeGateReqMessage* ageGate) {
        Debugger::Print("[AgeGateReqMessage]: age: %d", ageGate->GetAge());

        _connection->SendMessage(new AgeGateRspMessage());
    }

    void OnHomeServerSettingReqMessage(HomeServerSettingReqMessage* settingsRequest) {
        Debugger::Print("[HomeServerSettingReqMessage]: nope");

        _connection->SendMessage(new HomeServerSettingRspMessage());
    }

    void OnBattleStateCheckReqMessage(BattleStateCheckReqMessage* battleState) {
        Debugger::Print("[BattleStateCheckReqMessage]: nope");

        _connection->SendMessage(new BattleStateCheckRspMessage());
    }

    void OnHomePlayerDataReqMessage(HomePlayerDataReqMessage* request) {
        Debugger::Print("[HomePlayerDataReqMessage]: nope");

        _connection->SendMessage(new HomePlayerDataRspMessage());
    }

    void OnHomeReadGenericStorageReqMessage(HomeReadGenericStorageReqMessage* genericStorageRequest) {
        Debugger::Print("[HomeReadGenericStorageReqMessage]: nope");

        _connection->SendMessage(new HomeReadGenericStorageRspMessage());
    }
    
    void OnLeaderboardGetCurrentRankReqMessage(LeaderboardGetCurrentRankReqMessage* getRankRequest) {
        Debugger::Print("[LeaderboardGetCurrentRankReqMessage]: nope");

        _connection->SendMessage(new LeaderboardGetCurrentRankRspMessage());
    }

    void OnVoiceChatVerifyAgeResultReqMessage(VoiceChatVerifyAgeResultReqMessage* voiceChatVerifyRequest) {
        Debugger::Print("[VoiceChatVerifyAgeResultReqMessage]: age: %s", voiceChatVerifyRequest->GetAge());

        _connection->SendMessage(new VoiceChatVerifyAgeResultRspMessage());
    }

    void OnMatchMakeStartReqMessage(MatchMakeStartReqMessage* startRequest) {
        Debugger::Print("[MatchMakeStartReqMessage]: nope");

        _connection->SendMessage(new MatchMakeStateNotifyMessage());
        _connection->SendMessage(new MatchMakeStartRspMessage());
    }

    void OnLeaderboardInfoReqMessage(LeaderboardInfoReqMessage* leaderboardInfo) {
        Debugger::Print("[LeaderboardInfoReqMessage]: nope");

        _connection->SendMessage(new LeaderboardInfoRspMessage());
    }

    void OnSeasonShopFullInfoReqMessage(SeasonShopFullInfoReqMessage* shopRequest) {
        Debugger::Print("[SeasonShopFullInfoReqMessage]: nope");

        _connection->SendMessage(new SeasonShopFullInfoRspMessage());
    }

    void OnClientCryptoErrorMessage(ClientCryptoErrorMessage* cryptoError) {
        Debugger::Error("[ClientCryptoErrorMessage]: corrupted message type: %d", cryptoError->GetCorrputedMessageType());

        // if this somehow gonna be received, u need to resolve this error
        // and send clean message back as reply to this packet
    }
};

#undef cast_class