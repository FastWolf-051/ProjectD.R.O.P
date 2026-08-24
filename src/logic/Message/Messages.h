#pragma once

// list of all messages is here, to avoid ton of #includes in MessageManager and LogicBoardMessageFactory

#include "Login/LoginMessage.h"
#include "Login/LoginOkMessage.h"

#include "Pepper/ClientHelloMessage.h"
#include "Pepper/ServerHelloMessage.h"
#include "Pepper/ClientCryptoErrorMessage.h"

#include "Avatar/AvatarNameCheckRequestMessage.h"
#include "Avatar/AvatarNameCheckResponseMessage.h"
#include "Avatar/QuestGetDataReqMessage.h"
#include "Avatar/QuestGetDataRspMessage.h"

#include "Home/HomePlayerDataRspMessage.h"
#include "Home/DSClusterReqMessage.h"
#include "Home/DSClusterRspMessage.h"
#include "Home/KeepAliveMessage.h"
#include "Home/KeepAliveServerMessage.h"
#include "Home/AgeGateReqMessage.h"
#include "Home/AgeGateRspMessage.h"
#include "Home/HomeServerSettingRspMessage.h"
#include "Home/HomeServerSettingReqMessage.h"
#include "Home/BattleStateCheckReqMessage.h"
#include "Home/BattleStateCheckRspMessage.h"
#include "Home/HomePlayerDataReqMessage.h"
#include "Home/HomeReadGenericStorageReqMessage.h"
#include "Home/HomeReadGenericStorageRspMessage.h"
#include "Home/VoiceChatVerifyAgeResultReqMessage.h"
#include "Home/VoiceChatVerifyAgeResultRspMessage.h"
#include "Home/SeasonShopFullInfoRspMessage.h"
#include "Home/SeasonShopFullInfoReqMessage.h"

#include "Leaderboard/LeaderboardGetCurrentRankReqMessage.h"
#include "Leaderboard/LeaderboardGetCurrentRankRspMessage.h"
#include "Leaderboard/LeaderboardInfoRspMessage.h"
#include "Leaderboard/LeaderboardInfoReqMessage.h"

#include "Matchmake/MatchMakeStartReqMessage.h"
#include "Matchmake/MatchMakeStateNotifyMessage.h"
#include "Matchmake/MatchMakeStartRspMessage.h"

#define declare_message(name, type)