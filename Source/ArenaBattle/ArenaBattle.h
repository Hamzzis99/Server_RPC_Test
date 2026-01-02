// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole())) // 로컬 역할 정보를 로그에 표시하기 위한 매크로
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole())) // 원격 역할 정보를 로그에 표시하기 위한 매크로 (서버)
// 네트워크 모드 정보를 로그에 표시하기 위한 매크로
#if WITH_EDITOR
#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GetWorld() ? GetWorld()->GetOutermost()->GetPIEInstanceID() : 0) : \
((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : \
((GetNetMode() == ENetMode::NM_ListenServer) ? TEXT("LISTENSERVER") : TEXT("DEDICATEDSERVER"))))
#else
#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? TEXT("CLIENT") : \
((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : \
((GetNetMode() == ENetMode::NM_ListenServer) ? TEXT("LISTENSERVER") : TEXT("DEDICATEDSERVER"))))
#endif

#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__) // 언제 로그가 찍혔는지 알려주는 것?

// UELOG를 대체할 매크로? 궁금한데? 로그 카테고리, 로그레벨, 포맷, 가변인자 
// 출력 예시 : LogABNetwork: AABPlayerController::BeginPlay Begin
#define AB_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s][%s / %s] %s %s"), LOG_NETMODEINFO, LOG_LOCALROLEINFO, LOG_REMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogABNetwork, Log, All);