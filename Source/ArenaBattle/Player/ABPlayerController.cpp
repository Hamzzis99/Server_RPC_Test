// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ABSaveGame.h"
#include "ArenaBattle.h"

DEFINE_LOG_CATEGORY(LogABPlayerController);

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if (ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}

void AABPlayerController::PostInitializeComponents() // 네트워크와 무관하게 액터를 초기화 할 때 사용하는 것.
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin")); // 비긴 플레이가 실행되기 전에 이게 왜 나와?
	
	Super::PostInitializeComponents(); // 상위 클래스에 있는 대부분의 로직? 코딩 방식이 이상한데? 아, 오버라이드지 당연히 Super::니까

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABPlayerController::PostNetInit() // 원격 클라이언트로 초기화에 필요한 정보를 초기화 할 때 호출되는 것.
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin")); // 비긴 플레이가 실행되기 전에 이게 왜 나와?
	
	Super::PostNetInit(); // 상위 클래스에 있는 대부분의 로직? 코딩 방식이 이상한데? 아, 오버라이드지 당연히 Super::니까

	UNetDriver* NetDriver = GetNetDriver();
	
	if (NetDriver)
	{
		if (NetDriver -> ServerConnection)
		{
			AB_LOG(LogABNetwork, Log, TEXT("Server Connection(서버 커넥션): %s"), *NetDriver->ServerConnection->GetName());
		}
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver (넷드라이바 존재 없음)"));
	}
	
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABPlayerController::BeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin")); // 비긴 플레이가 실행되기 전에 이게 왜 나와?
	
	Super::BeginPlay(); // 상위 클래스에 있는 대부분의 로직? 코딩 방식이 이상한데? 아, 오버라이드지 당연히 Super::니까

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
	
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
