#pragma once

// list of all messages is here, to avoid ton of #includes in MessageManager and LogicBoardMessageFactory

#include "login/LoginMessage.h"
#include "login/LoginOkMessage.h"

#include "pepper/ClientHelloMessage.h"
#include "pepper/ServerHelloMessage.h"
#include "pepper/ClientCryptoErrorMessage.h"

#include "avatar/AvatarNameCheckRequestMessage.h"
#include "avatar/AvatarNameCheckResponseMessage.h"
#include "avatar/QuestGetDataReqMessage.h"
#include "avatar/QuestGetDataRspMessage.h"

#include "home/HomePlayerDataRspMessage.h"
#include "home/DSClusterReqMessage.h"
#include "home/DSClusterRspMessage.h"
#include "home/KeepAliveMessage.h"
#include "home/KeepAliveServerMessage.h"
#include "home/AgeGateReqMessage.h"
#include "home/AgeGateRspMessage.h"
#include "home/HomeServerSettingRspMessage.h"
#include "home/HomeServerSettingReqMessage.h"
#include "home/BattleStateCheckReqMessage.h"
#include "home/BattleStateCheckRspMessage.h"
#include "home/HomePlayerDataReqMessage.h"
#include "home/HomeReadGenericStorageReqMessage.h"
#include "home/HomeReadGenericStorageRspMessage.h"
#include "home/VoiceChatVerifyAgeResultReqMessage.h"
#include "home/VoiceChatVerifyAgeResultRspMessage.h"
#include "home/SeasonShopFullInfoRspMessage.h"
#include "home/SeasonShopFullInfoReqMessage.h"

#include "leaderboard/LeaderboardGetCurrentRankReqMessage.h"
#include "leaderboard/LeaderboardGetCurrentRankRspMessage.h"
#include "leaderboard/LeaderboardInfoRspMessage.h"
#include "leaderboard/LeaderboardInfoReqMessage.h"

#include "matchmake/MatchMakeStartReqMessage.h"
#include "matchmake/MatchMakeStateNotifyMessage.h"
#include "matchmake/MatchMakeStartRspMessage.h"

#define declare_message(name, type)